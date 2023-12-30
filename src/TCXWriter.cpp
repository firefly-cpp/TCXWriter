#include "TCXWriter.h"

TCXWriter::TCXWriter ()
{
}

void
TCXWriter::begin (const char *filename)
{
#if defined(ESP_PLATFORM)
  if (!SD_MMC.begin ())
    {
#elif defined(ARDUINO_ARCH_AVR)
  if (!SD.begin (10))
    {
#else
  // Add support also for the other platforms, e.g. ESP8266 # TODO
#endif
  Serial.println ("SD card initialization failed!");
  return;
}

#if defined(ESP_PLATFORM)
tcxFile = SD_MMC.open (filename, FILE_WRITE);
#elif defined(ARDUINO_ARCH_AVR)
tcxFile = SD.open (filename, FILE_WRITE);
#else
  // Add support also for the other platforms, e.g. ESP8266 # TODO
#endif

if (tcxFile)
  {
    tcxFile.println (F ("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"));
    tcxFile.
      println (F
	       ("<TrainingCenterDatabase xmlns=\"http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2\""));
    tcxFile.
      println (F
	       ("  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""));
    tcxFile.
      println (F
	       ("  xsi:schemaLocation=\"http://www.garmin.com/xmlschemas/TrainingCenterDatabase/v2 http://www.garmin.com/xmlschemas/TrainingCenterDatabasev2.xsd\">"));
    tcxFile.println (F ("  <Activities>"));
    tcxFile.println (F ("    <Activity Sport=\"Cycling\">"));	// # TODO: User should manually change this.
  }
else
  {
    Serial.println ("Error opening TCX file!");
  }
}

void
TCXWriter::addTrackpoint (float latitude, float longitude, float altitude,
			  int hr, int year, int month, int day, int hour,
			  int minute, int second)
{
  if (tcxFile)
    {
      char tcxtime[21];
      generateTCXTime (year, month, day, hour, minute, second, tcxtime);

      tcxFile.println (F ("      <Trackpoint>"));
      tcxFile.print (F ("        <Time>"));
      tcxFile.print (tcxtime);
      tcxFile.println (F ("</Time>"));
      tcxFile.println (F ("        <Position>"));
      tcxFile.print (F ("          <LatitudeDegrees>"));
      tcxFile.print (latitude, 4);
      tcxFile.println (F ("</LatitudeDegrees>"));
      tcxFile.print (F ("          <LongitudeDegrees>"));
      tcxFile.print (longitude, 4);
      tcxFile.println (F ("</LongitudeDegrees>"));
      tcxFile.println (F ("        </Position>"));
      tcxFile.print (F ("        <AltitudeMeters>"));
      tcxFile.print (altitude);
      tcxFile.println (F ("</AltitudeMeters>"));
      tcxFile.print (F ("        <HeartRateBpm>"));
      tcxFile.print (F ("<Value>"));
      tcxFile.print (hr);
      tcxFile.println (F ("</Value>"));
      tcxFile.println (F ("        </HeartRateBpm>"));
      tcxFile.println (F ("      </Trackpoint>"));
    }
  else
    {
      Serial.println ("TCX file not open!");
    }
}

void
TCXWriter::writeHeader (int year, int month, int day, int hour, int minute,
			int second)
{
  if (tcxFile)
    {
      char tcxtime[21];
      generateTCXTime (year, month, day, hour, minute, second, tcxtime);
      tcxFile.print (F ("      <Id>"));
      tcxFile.print (tcxtime);
      tcxFile.println (F ("</Id>"));
      tcxFile.println (F ("      <Lap>"));
    }
  else
    {
      Serial.println ("TCX file not open!");
    }
}

void
TCXWriter::writeFooter ()
{
  if (tcxFile)
    {
      tcxFile.println (F ("      </Lap>"));
      tcxFile.println (F ("    </Activity>"));
      tcxFile.println (F ("  </Activities>"));
      tcxFile.println (F ("</TrainingCenterDatabase>"));
      tcxFile.close ();
    }
  else
    {
      Serial.println ("TCX file not open!");
    }
}

void
TCXWriter::generateTCXTime (int year, int month, int day, int hour,
			    int minute, int second, char *tcxtime)
{
  snprintf(tcxtime, 21, "%04d-%02d-%02dT%02d:%02d:%02dZ", year, month, day, hour, minute, second);
}
