#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>

#if defined(_WIN32)
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

struct Telemetry {
    float soilMoisture;
    float temperature;
    float humidity;
    bool pumpActive;
};

int main() {
    bool pumpState = false;
    std::vector<Telemetry> history;

    std::cout << "Starting C++ Smart Agriculture Engine..." << std::endl;

    while (true) {
        std::ifstream dataFile("telemetry.dat");
        float soil = 0.0f, temp = 0.0f, hum = 0.0f;

        if (dataFile >> soil >> temp >> hum) {
            dataFile.close();

            // Automated Decision Logic
            if (soil < 30.0f) {
                pumpState = true;  // Soil is dry -> Turn ON water pump
            } else if (soil > 70.0f) {
                pumpState = false; // Soil is sufficiently moist -> Turn OFF water pump
            }

            // Send command signal to C sensor simulator
            std::ofstream cmdFile("pump_command.txt");
            if (cmdFile.is_open()) {
                cmdFile << (pumpState ? 1 : 0);
                cmdFile.close();
            }

            // Save telemetry log history (keep last 5 entries)
            Telemetry currentRead = {soil, temp, hum, pumpState};
            history.push_back(currentRead);
            if (history.size() > 5) history.erase(history.begin());

            // Render live terminal display
            std::system(CLEAR_SCREEN);
            std::cout << "========================================" << std::endl;
            std::cout << "   SMART AGRICULTURE MONITOR (C/C++)    " << std::endl;
            std::cout << "========================================" << std::endl;
            std::cout << " Soil Moisture : " << std::fixed << std::setprecision(1) << soil << " %" << std::endl;
            std::cout << " Temperature   : " << temp << " C" << std::endl;
            std::cout << " Air Humidity  : " << hum << " %" << std::endl;
            std::cout << " Water Pump    : " << (pumpState ? "[ ON - WATERING ]" : "[ OFF - IDLE ]") << std::endl;
            std::cout << "========================================" << std::endl;
            std::cout << "\nRecent Telemetry History:" << std::endl;
            std::cout << "Soil%\tTemp(C)\tHum%\tPump Status" << std::endl;
            std::cout << "----------------------------------------" << std::endl;

            for (const auto& log : history) {
                std::cout << log.soilMoisture << "%\t" 
                          << log.temperature << "\t" 
                          << log.humidity << "%\t" 
                          << (log.pumpActive ? "ON" : "OFF") << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    return 0;
}