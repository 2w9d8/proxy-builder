#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <sstream>
#include <limits>

using namespace std;

random_device rd;
mt19937 generator(rd());

int generateRandomPort() {
    uniform_int_distribution<int> distribution(1, 65535);
    return distribution(generator);
}

string generateRandomIP() {
    ostringstream ipBuilder;
    uniform_int_distribution<int> distribution(0, 255);

    for (int i = 0; i < 4; i++) {
        int octet = distribution(generator);
        ipBuilder << octet;

        if (i < 3) {
            ipBuilder << ".";
        }
    }

    return ipBuilder.str();
}

void storeProxy(const string& proxy) {
    ofstream outputFile("proxies.txt", ios_base::app);

    if (outputFile.is_open()) {
        outputFile << proxy << endl;
        outputFile.close();
        cout << "Successfully saved proxy: " << proxy << endl;
    }
    else {
        cout << "Failed to save proxy: " << proxy << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

      for (int x = numeric_limits<long>::min(); x < numeric_limits<long>::max(); x++) {
        string ip = generateRandomIP();
        int port = generateRandomPort();

        string proxy = ip + ":" + to_string(port);

        storeProxy(proxy);
    }

    return 0;
}
