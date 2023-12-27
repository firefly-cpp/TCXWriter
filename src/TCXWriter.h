/** @file TCXWriter.h
 *  @brief Function/procedure prototypes for TCXWriter library.
 *
 *  @note Laps are not yet supported in the current version.
 *  @author Iztok Fister Jr.
 *  @bug No known bugs.
 *  @version v1.0.0
 *  @date Last Change: 27.12.2023
 */

#ifndef TCXWRITER_H
#define TCXWRITER_H

#include <Arduino.h>

#if defined(ESP_PLATFORM)
#include <SD.h>
#elif defined(ARDUINO_ARCH_AVR)
#include <SD.h>
#else
#include <SD_MMC.h>
#endif

/**
 * @class TCXWriter
 *
 * @brief A class for writing data to a Training Center XML (TCX) file.
 */
class TCXWriter
{
public:
  /**
   * @brief Default constructor for TCXWriter.
   */
  TCXWriter ();

  /**
   * @brief Initializes the TCXWriter and opens the specified file.
   *
   * @param filename The name of the TCX file to be created.
   */
  void begin (const char *filename);

  /**
   * @brief Adds a trackpoint to the TCX file with the provided GPS and heart rate data.
   * @note: Add support for power-meter and cadence values.
   *
   * @param latitude Latitude of the trackpoint.
   * @param longitude Longitude of the trackpoint.
   * @param altitude Altitude of the trackpoint.
   * @param hr The heart rate Value.
   * @param year The year of the timestamp.
   * @param month The month of the timestamp.
   * @param day The day of the timestamp.
   * @param hour The hour of the timestamp.
   * @param minute The minute of the timestamp.
   * @param second The second of the timestamp.
   */
  void addTrackpoint (float latitude, float longitude, float altitude, int hr,
		      int year, int month, int day, int hour, int minute,
		      int second);

  /**
   * @brief Writes the header of the TCX file with the timestamp of activity/workout.
   *
   * @param year The year of the timestamp.
   * @param month The month of the timestamp.
   * @param day The day of the timestamp.
   * @param hour The hour of the timestamp.
   * @param minute The minute of the timestamp.
   * @param second The second of the timestamp.
   */
  void writeHeader (int year, int month, int day, int hour, int minute,
		    int second);

  /**
   * @brief Writes the footer of the TCX file.
   */
  void writeFooter ();

private:
    File tcxFile;		// File object.

  /**
   * @brief Generates a formatted TCX time string.
   *
   * @param year The year of the timestamp.
   * @param month The month of the timestamp.
   * @param day The day of the timestamp.
   * @param hour The hour of the timestamp.
   * @param minute The minute of the timestamp.
   * @param second The second of the timestamp.
   * @param tcxtime Pointer to the character array for storing the generated time string.
   */
  void generateTCXTime (int year, int month, int day, int hour, int minute,
			int second, char *tcxtime);
};

#endif
