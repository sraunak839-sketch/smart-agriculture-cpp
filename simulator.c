#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Handle sleep cross-platform (Windows vs Linux/Mac)
#if defined(_WIN32)
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
#endif

int main() {
    float soilMoisture = 50.0f;
    float temperature = 24.5f;
    float humidity = 60.0f;

    srand((unsigned int)time(NULL));

    printf("Starting C Virtual Sensor Simulator...\n");

    while (1) {
        // 1. Read command from the C++ dashboard
        FILE *cmdFile = fopen("pump_command.txt", "r");
        int pumpState = 0;
        if (cmdFile != NULL) {
            fscanf(cmdFile, "%d", &pumpState);
            fclose(cmdFile);
        }

        // 2. Adjust environmental simulation state
        if (pumpState == 1) {
            soilMoisture += 8.0f; // Pump ON: soil gets wet
            if (soilMoisture > 85.0f) soilMoisture = 85.0f;
        } else {
            soilMoisture -= 1.5f; // Pump OFF: soil dries out
            if (soilMoisture < 10.0f) soilMoisture = 10.0f;
        }

        // 3. Add small random fluctuations to temperature and humidity
        temperature += ((rand() % 100) / 100.0f - 0.5f) * 0.4f;
        humidity += ((rand() % 100) / 100.0f - 0.5f) * 0.8f;

        // 4. Output current sensor values to telemetry.dat
        FILE *dataFile = fopen("telemetry.dat", "w");
        if (dataFile != NULL) {
            fprintf(dataFile, "%.2f %.2f %.2f\n", soilMoisture, temperature, humidity);
            fclose(dataFile);
        }

        sleep_ms(2000); // Send new telemetry reading every 2 seconds
    }

    return 0;
}