#ifndef SCSERIAL_H
#define SCSERIAL_H

// Remove Qt Dependency
// #include <QObject>
// #include <QSerialPort>
// #include <QString>

#include "../SerialPort.hpp" // Custom SerialPort class used instead of QSerialPort
#include <map>
#include <string>
#include <vector>


#define INST_PING 0x01
#define INST_READ 0x02
#define INST_WRITE 0x03
#define INST_REG_WRITE 0x04
#define INST_REG_ACTION 0x05
#define INST_SYNC_READ 0x82
#define INST_SYNC_WRITE 0x83

#include "servo_types.h"

namespace feetech_servo {

std::string getModelType(uint16_t id); // QString -> std::string

enum ModelSeries { SMCL, SMBL, STS, SCS };

ModelSeries getModelSeries(std::string modelName); // QString -> std::string

class SCSerial {
public:
  SCSerial(SerialPort *serial); // QSerialPort* -> SerialPort*

  void set_end(uint8_t end) { end_ = end; }

  int gen_write(uint8_t id, uint8_t mem_addr, uint8_t *n_dat, uint8_t n_len);
  int reg_write(uint8_t id, uint8_t mem_addr, uint8_t *n_dat, uint8_t n_len);
  int reg_write_action(uint8_t id = 0xfe);
  void sync_write(uint8_t id[], uint8_t idn, uint8_t mem_addr, uint8_t *n_dat,
                  uint8_t n_len);
  int write_byte(uint8_t id, uint8_t mem_addr, uint8_t b_dat);
  int write_word(uint8_t id, uint8_t mem_addr, uint16_t w_dat);
  int read(uint8_t id, uint8_t mem_addr, uint8_t *n_data, uint8_t n_len);
  int read_byte(uint8_t id, uint8_t mem_addr);
  int read_word(uint8_t id, uint8_t mem_addr);
  int ping(uint8_t id);
  int write(uint8_t *n_dat, int n_len);
  int read(uint8_t *n_dat, int n_len);
  int write(uint8_t b_dat);
  void read_flush() { /* do not anything, maybe clear buffer? */ }
  void write_flush() { /* do not anything */ }
  int read_model_number(int id);

  void set_timeout(uint16_t timeout) { timeout_ = timeout; }

  void write_buf(uint8_t id, uint8_t mem_addr, uint8_t *n_dat, uint8_t n_len,
                 uint8_t fun);
  void host_2_scs(uint8_t *data_l, uint8_t *data_h, uint16_t data);
  uint16_t scs_2_host(uint8_t data_l, uint8_t data_h);
  int ask(uint8_t id);
  int check_head();

  // Getter for serial port (if needed)
  SerialPort *serial() const { return serial_; }

protected:
  uint8_t level_;
  uint8_t end_;
  uint8_t error_;
  uint8_t sync_read_rx_packet_index_;
  uint8_t sync_read_rx_packet_len_;
  uint8_t *sync_read_rx_packet_;

  SerialPort *serial_;
  uint16_t timeout_ = 50;
};

} // namespace feetech_servo

#include "scscl.h"
#include "sms_sts.h"


#endif // SCSERIAL_H
