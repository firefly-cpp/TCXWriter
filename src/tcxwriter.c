#include "tcxwriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void
tcx_current_timestamp (char *tcxDatetimeFormat)
{
  time_t raw;
  struct tm *utc;

  // current time
  time (&raw);
  utc = gmtime (&raw);		// get UTC

  // Use proper TCX format
  strftime (tcxDatetimeFormat, 20, "%Y-%m-%dT%H:%M:%SZ", utc);
}

void
tcx_add_trackpoint (Track *track, float latitude, float longitude,
		    float altitude, int hr)
{

  // Obtain the current timestamp
  char timestamp[20];
  tcx_current_timestamp (timestamp);

  // @todo: Check whether the data is null and whether there are other discrepancies before creating a new Trackpoint.

  // New trackpoint
  Trackpoint new_trackpoint;
  snprintf (new_trackpoint.timestamp, sizeof (new_trackpoint.timestamp), "%s",
	    timestamp);
  new_trackpoint.latitude = latitude;
  new_trackpoint.longitude = longitude;
  new_trackpoint.altitude = altitude;
  new_trackpoint.hr = hr;

  // Resize the array
  track->points =
    realloc (track->points, (track->size + 1) * sizeof (Trackpoint));
  if (track->points != NULL)
    {
      track->points[track->size] = new_trackpoint;
      track->size++;
    }
  else
    {
      // Report problems when storing
      printf
	("Error: Memory allocation failed when adding a new TrackPoint.\n");
    }
}

void
tcx_write_to_file (const char *filename, const Track *track)
{
  // open a file
  FILE *file = fopen (filename, "w");
  if (file == NULL)
    {
      perror ("Error opening file!");
      return;
    }

  // Write TCX header
  fprintf (file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf (file,
	   "<TrainingCenterDatabase xmlns=\"http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2\"\n");
  fprintf (file,
	   "  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n");
  fprintf (file,
	   "  xsi:schemaLocation=\"http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2 http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd\">\n");
  fprintf (file, "  <Activities>\n");
  fprintf (file, "    <Activity Sport=\"Cycling\">\n");	// @todo: Support user-defined entry
  fprintf (file, "      <Id>%s</Id>\n", track->points[0].timestamp);	// Use the timestamp of the first trackpoint as the activity ID

  // Write each trackpoint to file
  for (size_t i = 0; i < track->size; ++i)
    {
      fprintf (file, "      <Trackpoint>\n");
      fprintf (file, "        <Time>%s</Time>\n", track->points[i].timestamp);
      fprintf (file, "        <Position>\n");
      fprintf (file, "          <LatitudeDegrees>%f</LatitudeDegrees>\n",
	       track->points[i].latitude);
      fprintf (file, "          <LongitudeDegrees>%f</LongitudeDegrees>\n",
	       track->points[i].longitude);
      fprintf (file, "        </Position>\n");
      fprintf (file, "        <AltitudeMeters>%f</AltitudeMeters>\n",
	       track->points[i].altitude);
      fprintf (file, "        <HeartRateBpm>\n");
      fprintf (file, "          <Value>%d</Value>\n", track->points[i].hr);
      fprintf (file, "        </HeartRateBpm>\n");
      fprintf (file, "      </Trackpoint>\n");
    }

  // Write TCX footer
  fprintf (file, "    </Activity>\n");
  fprintf (file, "  </Activities>\n");
  fprintf (file, "</TrainingCenterDatabase>\n");

  // Close the file
  fclose (file);
}

// Free memory at the end
void
tcx_free (Track *track)
{
  free (track->points);
}

int
main ()
{
  // A minimal example

  //Track activity = { NULL, 0 };       // Init the track

  // Add two trackpoints

  //tcx_add_trackpoint (&activity, 1, -1, 100.0, 120);
  //tcx_add_trackpoint (&activity, 1.1, -.2, 101.0, 125);

  //tcx_write_to_file ("activity.tcx", &activity);

  // Free allocated memory
  //tcx_free (&activity);

  return 0;
}
