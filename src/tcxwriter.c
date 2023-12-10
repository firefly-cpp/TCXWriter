#include "tcxwriter.h"
#include <stdio.h>
#include <string.h>

static FILE *file;

// schemas related content
const char *xmlSchema = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "<TrainingCenterDatabase\n"
  "  xsi:schemaLocation=\"http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2 http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd\"\n"
  "  xmlns:ns5=\"http://www.garmin.com/xmlschemas/ActivityGoals/v1\"\n"
  "  xmlns:ns3=\"http://www.garmin.com/xmlschemas/ActivityExtension/v2\"\n"
  "  xmlns:ns2=\"http://www.garmin.com/xmlschemas/UserProfile/v2\"\n"
  "  xmlns=\"http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2\"\n"
  "  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:ns4=\"http://www.garmin.com/xmlschemas/ProfileExtension/v1\">\n"
  "  <Activities>\n";

void
tcx_init (const char *filename, int *error)
{
  // open a file
  file = fopen (filename, "w");
  if (file == NULL)
    {
      *error = -1;
      return;
    }

  // Init a header in file
  size_t len = strlen (xmlSchema);
  size_t written = fwrite (xmlSchema, sizeof (char), len, file);

  // Check for errors during the write process
  if (written != len)
    {
      *error = -1;
      return;
      fclose (file);
    }
}

void
tcx_add_trackpoint (uint32_t timestamp, float latitude, float longitude,
		    float altitude, int heart_rate)
{
  // Add a new trackpoint to the TCX file
  fprintf (file, "<Trackpoint>\n");
  fprintf (file, "  <Time>%u</Time>\n", timestamp);

  // TODO

  fprintf (file, "</Trackpoint>\n");
}

void
tcx_finalize ()
{
  // Close the file
  fclose (file);
}

int
main ()
{
  // TODO
  int error = 0;
  tcx_init ("activity.tcx", &error);

  return 0;
}
