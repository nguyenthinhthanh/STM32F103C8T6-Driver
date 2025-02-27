# STM32F103C8T6 Drivers - GPIO, Timer, I2C, SPI

## 🚀 Mô tả dự án
Dự án này bao gồm các driver cơ bản cho vi điều khiển **STM32F103C8T6**, được viết từ đầu mà không sử dụng HAL hoặc LL của STM32Cube. Các driver hỗ trợ **GPIO, Timer, I2C, SPI**, giúp bạn dễ dàng làm chủ phần cứng ở mức thấp.

## 📌 Tính năng chính
- **GPIO Driver:** Cấu hình input/output, pull-up/pull-down, ngắt ngoại vi.
- **Timer Driver:** Cấu hình timer ở chế độ basic, PWM, input capture.
- **I2C Driver:** Hỗ trợ chế độ master/slave, giao tiếp với các cảm biến.
- **SPI Driver:** Hỗ trợ SPI master/slave, full-duplex.

## 💻 Công nghệ sử dụng
- **Ngôn ngữ:** C
- **IDE:** STM32CubeIDE
- **Thư viện:** CMSIS
- **Phần cứng:** Blue Pill (STM32F103C8T6)


## 🛠 Hướng dẫn sử dụng
### 1️⃣ Clone repo
```bash
git clone https://github.com/nguyenthinhthanh/STM32F103C8T6-Driver
```
### 2️⃣ Thêm thư mục Drivers/ vào dự án STM32CubeIDE
- Sao chép thư mục Drivers/ vào thư mục dự án của bạn.
- Thêm đường dẫn Drivers/ vào Include Paths trong STM32CubeIDE.
### 3️⃣ Viết chương trình chính (main.c) để sử dụng driver

## 🤝 Đóng góp
Bạn có ý tưởng cải thiện trò chơi? Hãy mở Pull Request hoặc Issue trên GitHub!

## 📄 Giấy phép
Null.

