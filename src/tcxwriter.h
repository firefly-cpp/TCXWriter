/** @file tcxwriter.h
 *  @brief Function/procedure prototypes for tcxwriter library.
 *
 *  @note Laps are not yet supported in the current version.
 *  @author Iztok Fister Jr.
 *  @bug No known bugs.
 *  @version v@TCXWRITER_VERSION_MAJOR@.@TCXWRITER_VERSION_MINOR@.@TCXWRITER_VERSION_PATCH@
*   @date Last Change: 11.12.2023
 */
#ifndef TCXWRITER_H
#define TCXWRITER_H

// Version information
#define TCXWRITER_VERSION_MAJOR 0
#define TCXWRITER_VERSION_MINOR 1
#define TCXWRITER_VERSION_PATCH 0

#include <stddef.h>
#include <stdint.h>

/**
 * @brief The structure represents a trackpoint with timestamp, location (latitude and longitude), altitude, and heart rate.
 * @note We should also consider storing cadence and wattmeter values and steps in the future version.
 */
typedef struct trackpoint
{
  char timestamp[20]; /**< Timestamp in "YYYY-MM-DDThh:mm:ssZ" format */
  float latitude;     /**< Latitude of the trackpoint */
  float longitude;    /**< Longitude of the trackpoint */
  float altitude;     /**< Altitude of the trackpoint */
  int hr;	      /**< Heart rate of the trackpoint */
} Trackpoint;

/**
 * @brief The structure represents a track with an array of track points and sizes.
 */
typedef struct track
{
  Trackpoint *points;	/**< Array of trackpoints */
  size_t size;		/**< Size of the track (number of trackpoints) */
} Track;

/**
 * @brief Function to get the current timestamp in TCX format.
 *
 * @param[out] tcxFormat Buffer to store the TCX-formatted timestamp.
 */
void tcx_current_timestamp (char *tcxFormat);

/**
 * @brief Function to add a trackpoint to a track.
 *
 * @param[in,out] track Pointer to the track structure.
 * @param[in] latitude Latitude of the trackpoint.
 * @param[in] longitude Longitude of the trackpoint.
 * @param[in] altitude Altitude of the trackpoint.
 * @param[in] hr Heart rate of the trackpoint.
 */
void tcx_add_trackpoint (Track * track, float latitude, float longitude,
			 float altitude, int hr);

/**
 * @brief Function to write track points in TCX format to a file.
 *
 * @param[in] filename Name of the TCX file.
 * @param[in] track Pointer to the track structure.
 */
void tcx_write_to_file (const char *filename, const Track * track);

/**
 * @brief Free memory at the end of the process.
 *
 * @param[in] track Pointer to the track structure.
 */
void tcx_free (Track * track);

/**
 * @todo Consider adding metadata, e.g., device name, to the file.
 * @note Not yet implemented.
 */
void tcx_add_metadata ();

#endif // TCXWRITER_H
