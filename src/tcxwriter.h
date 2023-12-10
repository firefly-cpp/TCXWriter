/** @file tcxwriter.h
 *  @brief Function/procedure prototypes for tcxwriter library.
 *
 *  #TODO
 *
 *
 *  @author Iztok Fister Jr.
 *  @bug No known bugs.
 */
#ifndef TCXWRITER_H
#define TCXWRITER_H

#include <stdint.h>

/** @struct trackpoint
 *  @brief The structure represents a trackpoint.
 *  @var trackpoint::timestamp
 *  TODO
 *  @var trackpoint::latitude
 *  TODO
 *  @var trackpoint::longitude
 *  TODO
 *  @var trackpoint::altitude
 *  TODO
 *  @var trackpoint::hr
 *  TODO
 */
typedef struct trackpoint
{
  uint32_t timestamp;
  float latitude;
  float longitude;
  float altitude;
  int hr;
};

/**
 * The procedure that initiates (opens) a file for writing content into.
 * @param[in] filename
 */
void tcx_init(const char *filename, int* error);

/**
 * Main procedure for writing track points into a file.
 * @param[in] timestamp
 * @param[in] altitude
 * @param[in] longitude
 * @param[in] altitude
 * @param[in] hr
 */
void tcx_add_trackpoint(uint32_t timestamp, float latitude, float longitude, float altitude, int hr);
/**
 * The procedure that writes metadata (e.g., device name) to the TCX file.
 * @param[in] device_name
 */
void tcx_add_metadata();
/**
 * Procedure for validating a composed TCX file.
 * @param[in] X
 */
void tcx_validate();

/**
 * Close the file.
 */
void tcx_finalize();

#endif // TCXWRITER_H
