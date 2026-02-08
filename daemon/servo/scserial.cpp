#include "scserial.h"

namespace feetech_servo {

#define SERVO_MODEL(major, minor, name) {(minor << 8 | major), name}

std::string getModelType(uint16_t id) {
  static std::map<uint16_t, std::string> model_list = {
      SERVO_MODEL(5, 0, "SCSXX"),
      SERVO_MODEL(5, 4, "SCS009"),
      // ... (필요한 모델 추가, 너무 많으면 생략 가능하지만 핑 테스트를 위해 몇
      // 개는 유지)
      SERVO_MODEL(9, 3, "STS3215"),
      SERVO_MODEL(9, 2, "STS3032"),
      SERVO_MODEL(9, 0, "STSXX"),
      SERVO_MODEL(5, 15, "SCS15"),
  };

  if (auto it = model_list.find(id); it != model_list.end()) {
    return it->second;
  }

  return "Unknown";
}
#undef SERVO_MODEL

ModelSeries getModelSeries(std::string modelName) {
  // C++20 starts_with 대신
  if (modelName.find("STS") == 0) {
    return STS;
  } else if (modelName.find("SC") == 0) {
    return SCS;
  } else if (modelName.find("SM") == 0 &&
             modelName.find("BL") != std::string::npos) {
    return SMBL;
  } else {
    return SMCL;
  }
}

SCSerial::SCSerial(SerialPort *serial) : serial_(serial) {
  level_ = 1;
  error_ = 0;
  end_ = 0;
}

int SCSerial::gen_write(uint8_t id, uint8_t mem_addr, uint8_t *n_dat,
                        uint8_t n_len) {
  read_flush();
  write_buf(id, mem_addr, n_dat, n_len, INST_WRITE);
  write_flush();
  return ask(id);
}

int SCSerial::reg_write(uint8_t id, uint8_t mem_addr, uint8_t *n_dat,
                        uint8_t n_len) {
  read_flush();
  write_buf(id, mem_addr, n_dat, n_len, INST_REG_WRITE);
  write_flush();
  return ask(id);
}

int SCSerial::reg_write_action(uint8_t id) {
  read_flush();
  write_buf(id, 0, NULL, 0, INST_REG_ACTION);
  write_flush();
  return ask(id);
}

void SCSerial::sync_write(uint8_t id[], uint8_t idn, uint8_t mem_addr,
                          uint8_t *n_dat, uint8_t n_len) {
  read_flush();
  uint8_t mes_len = ((n_len + 1) * idn + 4);
  uint8_t sum = 0;
  uint8_t b_buf[7];
  b_buf[0] = 0xff;
  b_buf[1] = 0xff;
  b_buf[2] = 0xfe;
  b_buf[3] = mes_len;
  b_buf[4] = INST_SYNC_WRITE;
  b_buf[5] = mem_addr;
  b_buf[6] = n_len;
  write(b_buf, 7);

  sum = 0xfe + mes_len + INST_SYNC_WRITE + mem_addr + n_len;
  uint8_t i, j;
  for (i = 0; i < idn; i++) {
    write(id[i]);
    write(n_dat + i * n_len, n_len);
    sum += id[i];
    for (j = 0; j < n_len; j++) {
      sum += n_dat[i * n_len + j];
    }
  }
  write(~sum);
  write_flush();
}

int SCSerial::write_byte(uint8_t id, uint8_t mem_addr, uint8_t b_dat) {
  read_flush();
  write_buf(id, mem_addr, &b_dat, 1, INST_WRITE);
  write_flush();
  return ask(id);
}

int SCSerial::write_word(uint8_t id, uint8_t mem_addr, uint16_t w_dat) {
  uint8_t b_buf[2];
  host_2_scs(b_buf + 0, b_buf + 1, w_dat);
  read_flush();
  write_buf(id, mem_addr, b_buf, 2, INST_WRITE);
  write_flush();
  return ask(id);
}

int SCSerial::read(uint8_t id, uint8_t mem_addr, uint8_t *n_data,
                   uint8_t n_len) {
  read_flush();
  write_buf(id, mem_addr, &n_len, 1, INST_READ);
  write_flush();
  if (!check_head()) {
    return 0;
  }
  uint8_t b_buf[4];
  error_ = 0;
  if (read(b_buf, 3) != 3) {
    return 0;
  }
  int size = read(n_data, n_len);
  if (size != n_len) {
    return 0;
  }
  if (read(b_buf + 3, 1) != 1) {
    return 0;
  }
  uint8_t cal_sum = b_buf[0] + b_buf[1] + b_buf[2];
  uint8_t i;
  for (i = 0; i < size; i++) {
    cal_sum += n_data[i];
  }
  cal_sum = ~cal_sum;
  if (cal_sum != b_buf[3]) {
    return 0;
  }
  error_ = b_buf[2];
  return size;
}

int SCSerial::read_byte(uint8_t id, uint8_t mem_addr) {
  uint8_t b_dat;
  int size = read(id, mem_addr, &b_dat, 1);
  if (size != 1) {
    return -1;
  } else {
    return b_dat;
  }
}

int SCSerial::read_word(uint8_t id, uint8_t mem_addr) {
  uint8_t n_dat[2];
  int size;
  uint16_t w_dat;
  size = read(id, mem_addr, n_dat, 2);
  if (size != 2)
    return -1;
  w_dat = scs_2_host(n_dat[0], n_dat[1]);
  return w_dat;
}

int SCSerial::ping(uint8_t id) {
  read_flush();
  write_buf(id, 0, NULL, 0, INST_PING);
  write_flush();
  error_ = 0;
  if (!check_head()) {
    return -1;
  }
  uint8_t b_buf[4];
  if (read(b_buf, 4) != 4) {
    return -1;
  }
  if (b_buf[0] != id && id != 0xfe) {
    return -1;
  }
  if (b_buf[1] != 2) {
    return -1;
  }
  uint8_t cal_sum = ~(b_buf[0] + b_buf[1] + b_buf[2]);
  if (cal_sum != b_buf[3]) {
    return -1;
  }
  error_ = b_buf[2];
  return b_buf[0];
}

void SCSerial::write_buf(uint8_t id, uint8_t mem_addr, uint8_t *n_dat,
                         uint8_t n_len, uint8_t fun) {
  uint8_t msg_len = 2;
  uint8_t b_buf[6];
  uint8_t check_sum = 0;
  b_buf[0] = 0xff;
  b_buf[1] = 0xff;
  b_buf[2] = id;
  b_buf[4] = fun;
  if (n_dat) {
    msg_len += n_len + 1;
    b_buf[3] = msg_len;
    b_buf[5] = mem_addr;
    write(b_buf, 6);

  } else {
    b_buf[3] = msg_len;
    write(b_buf, 5);
  }
  check_sum = id + msg_len + fun + mem_addr;
  uint8_t i = 0;
  if (n_dat) {
    for (i = 0; i < n_len; i++) {
      check_sum += n_dat[i];
    }
    write(n_dat, n_len);
  }
  write(~check_sum);
}

void SCSerial::host_2_scs(uint8_t *data_l, uint8_t *data_h, uint16_t data) {
  if (end_) {
    *data_l = (data >> 8);
    *data_h = (data & 0xff);
  } else {
    *data_h = (data >> 8);
    *data_l = (data & 0xff);
  }
}

uint16_t SCSerial::scs_2_host(uint8_t data_l, uint8_t data_h) {
  uint16_t data;
  if (end_) {
    data = data_l;
    data <<= 8;
    data |= data_h;
  } else {
    data = data_h;
    data <<= 8;
    data |= data_l;
  }
  return data;
}

int SCSerial::ask(uint8_t id) {
  error_ = 0;
  if (id != 0xfe && level_) {
    if (!check_head()) {
      return 0;
    }
    uint8_t b_buf[4];
    if (read(b_buf, 4) != 4) {
      return 0;
    }
    if (b_buf[0] != id) {
      return 0;
    }
    if (b_buf[1] != 2) {
      return 0;
    }
    uint8_t cal_sum = ~(b_buf[0] + b_buf[1] + b_buf[2]);
    if (cal_sum != b_buf[3]) {
      return 0;
    }
    error_ = b_buf[2];
  }
  return 1;
}

int SCSerial::check_head() {
  uint8_t b_dat;
  uint8_t b_buf[2] = {0, 0};
  uint8_t cnt = 0;
  while (1) {
    if (!read(&b_dat, 1)) {
      return 0;
    }
    b_buf[1] = b_buf[0];
    b_buf[0] = b_dat;
    if (b_buf[0] == 0xff && b_buf[1] == 0xff) {
      break;
    }
    cnt++;
    if (cnt > 10) {
      return 0;
    }
  }
  return 1;
}

int SCSerial::read_model_number(int id) {
  int tmp = -1;
  int model_number = -1;
  {
    error_ = 0;
    tmp = read_byte(id, 3); // 3 : Servo Main Version, 4 : Servo Sub Version
    if (tmp == -1) {
      error_ = 1;
    } else {
      model_number = tmp;
      {
        tmp = read_byte(id, 4);
        if (tmp == -1) {
          error_ = 1;
        } else {
          model_number |= tmp << 8;
        }
      }
    }
  }
  return model_number;
}

int SCSerial::write(uint8_t *n_dat, int n_len) {
  if (!serial_)
    return -1;
  // reinterpret_cast<const char *>로 캐스팅
  return serial_->write(reinterpret_cast<const char *>(n_dat), n_len);
}

int SCSerial::read(uint8_t *n_dat, int n_len) {
  if (!serial_)
    return -1;
  // bytesAvailable() 사용
  if (serial_->bytesAvailable() < n_len)
    serial_->waitForReadyRead(timeout_);

  return serial_->read(reinterpret_cast<char *>(n_dat), n_len);
}

int SCSerial::write(uint8_t b_dat) {
  if (!serial_)
    return -1;
  return serial_->write(reinterpret_cast<const char *>(&b_dat), 1);
}

} // namespace feetech_servo
