#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include <Arduino.h>

class NMEAParser {
private:
    // Position data
    float latitude = 0.0;
    float longitude = 0.0;
    char latDir = 'N';
    char lonDir = 'E';
    
    // Navigation data
    float speed = 0.0;
    float course = 0.0;
    float altitude = 0.0;
    
    // Time and date
    String time = "000000.000";
    String date = "010100";
    
    // Satellite data
    int satellites = 0;
    float hdop = 99.99;   // Horizontal dilution of precision
    float vdop = 99.99;   // Vertical dilution of precision
    float pdop = 99.99;   // Position dilution of precision

    // Status flags
    bool newData = false;
    bool validPosition = false;
    bool validAltitude = false;
    bool validHDOP = false;
    bool validPDOP = false;
    bool validVDOP = false;
    
    // NMEA data
    
    // Satellite tracking
    static const int MAX_SATELLITES = 32;
    struct SatelliteInfo {
        int id = 0;
        int elevation = 0;  // 0-90 degrees
        int azimuth = 0;    // 0-359 degrees
        int snr = 0;        // Signal-to-noise ratio (0-99 dB)
        bool used = false;  // Whether satellite is used in position fix
    };
    SatelliteInfo satellites_info[MAX_SATELLITES];
    int satellites_count = 0;
    bool satellites_updated = false;
    
    // NMEA sentence parsing
    String currentSentence = "";
    bool parsingGGA = false;
    bool parsingRMC = false;
    bool parsingGSA = false;
    bool parsingGSV = false;
    
    // Helper methods
    void parseGGA(String sentence);
    void parseRMC(String sentence);
    void parseGSA(String sentence);
    void parseGSV(String sentence);
    float convertToDecimalDegrees(String pos, char dir);
    bool checkSentenceChecksum(String sentence);

public:
    NMEAParser();
    
    void processGPSData(char c);
    bool isNewDataAvailable();
    void clearNewDataFlag();
    
    // Position getters
    float getLatitude();
    float getLongitude();
    String getPositionString();
    
    // Navigation getters
    float getSpeed();
    float getCourse();
    float getAltitude();
    bool hasAltitude();
    
    // Time and date getters
    String getTimeString();
    String getDateString();
    
    // Satellite data getters
    int getSatellites();
    float getHDOP();
    bool hasHDOP();
    float getVDOP();
    bool hasVDOP();
    float getPDOP();
    bool hasPDOP();

    // Status getters
    bool hasValidPosition();
    bool hasValidFix();
    int getFixQuality();  // 0=no fix, 1=GPS fix, 2=DGPS fix
    
    // For satellite view screen
    // Return array of visible satellites (up to maxCount)
    int getSatelliteInfo(SatelliteInfo* satArray, int maxCount);
    
    // Get a specific satellite's information
    bool getSatelliteById(int id, SatelliteInfo& satInfo);
    
    // Check if satellite data has been updated
    bool isSatelliteDataUpdated();
    void clearSatelliteDataUpdatedFlag();

    // Additional GPS data getters
    String getFixTypeString();
};

#endif // NMEA_PARSER_H
