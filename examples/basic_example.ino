#include <TCXWriter.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TCXWriter tcx;

TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(4, 3);

void setup() {
  Serial.begin(115200);

  ss.begin(9600);

  // Initialize the TCXWriter
  tcx.begin("abc.tcx");

  // Example usage
  tcx.writeHeader(2023, 1, 1, 12, 30, 0);  // Use the actual start time from your GPS data
  
}

int c = 0; // Let's write 10 trackpoints into the file and stop.

void loop() {

  
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      tcx.addTrackpoint(gps.location.lat(), gps.location.lng(), gps.altitude.meters(), 120, gps.date.year(), gps.date.month(), gps.date.day(), gps.time.hour(), gps.time.minute(), gps.time.second());
      c++;
      if (c == 10)
      {
        tcx.writeFooter();
        while(1) {};
      }
    }
  } 
}
