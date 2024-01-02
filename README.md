# tcxwriter -- A Tiny Library for writing/creating TCX files on Arduino & ESP32 devices

---

[![Arduino-lint](https://github.com/firefly-cpp/TCXWriter/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/firefly-cpp/TCXWriter/actions/workflows/arduino-lint.yml)
![GitHub repo size](https://img.shields.io/github/repo-size/firefly-cpp/TCXWriter?style=flat-square)
[![GitHub license](https://img.shields.io/github/license/firefly-cpp/TCXWriter.svg)](https://github.com/firefly-cpp/TCXWriter/blob/master/LICENSE)
![GitHub commit activity](https://img.shields.io/github/commit-activity/w/firefly-cpp/TCXWriter.svg)

## About

TCXWriter is a lightweight library designed for Arduino and ESP32 projects that involves recording and storing GPS and heart rate data in the Training Center XML (TCX) file format. This library simplifies creating TCX files by providing intuitive functions to initialize, add trackpoints, and finalize TCX files. It seamlessly integrates with Arduino's SD library, making it compatible with various platforms. The TCXWriter framework enables developers to effortlessly log location and health data during activities such as cycling or running, facilitating easy analysis and visualization of performance metrics. Primarily, it was designed to support the development of lightweight sports trackers.

## Supported devices

TCXWriter should, in theory, work on all Arduino devices, but those specific devices have been reported as working:

- Arduino Nano

## How to read/parse TCX files?

Reading/parsing TCX files can be quickly done using the following software packages or frameworks:

- [sport-activities-features](https://github.com/firefly-cpp/sport-activities-features)
- [tcxreader](https://github.com/alenrajsp/tcxreader)

## Related frameworks

[AST-Monitor](https://github.com/firefly-cpp/AST-Monitor)

## License

This package is distributed under the MIT License. This license can be found online at <http://www.opensource.org/licenses/MIT>.

## Disclaimer

This library/framework is provided as-is, and there are no guarantees that it fits your purposes or that it is bug-free. Use it at your own risk!
