//
//  main.cpp
//  races
//
//  Created by Sara Nikolić on 05.11.2020.
//  Copyright © 2020 Sara Nikolić. All rights reserved.
//

#include <iostream>
#include "Races.hpp"

int main() {
    try {
        GameEngine re1;

        // Start EarthRace
        Race* Erace1 = new Race("Earth", 500);
        re1.createRace(Erace1);
        Race* Erace2 = new Race("Earth", 15);
        re1.setRace(Erace2);
        Transport* transport = new TwoHumpCamel();
        re1.putVehicle(transport);
        Transport* transport2 = new MagicBoots();
        re1.putVehicle(transport2);
        Transport* transport3 = new Centaur();
        re1.putVehicle(transport3);
        Transport* transport4 = new FastCamel();
        re1.putVehicle(transport4);
        re1.removeVehicle("centaur");
        re1.printContestants();
        std::string result = re1.runRace();
        std::cout << "\nThe winner of this race is " << result << "\n\n";
        re1.stopRace();
        // Stop EarthRace
        
        // Start AirRace
        Race* Arace1 = new Race("Air", 600);
        re1.createRace(Arace1);
        Transport* transport11 = new Broom();
        re1.putVehicle(transport11);
        Transport* transport22 = new Cane();
        re1.putVehicle(transport22);
        Transport* transport33 = new MagicCarpet();
        re1.putVehicle(transport33);
        re1.printContestants();
        std::string result2 = re1.runRace();
        std::cout << "\nThe winner of this race is " << result2 << "\n\n";
        re1.stopRace();
        // Stop AirRace
        
        // Start BothRace
        Race* Brace1 = new Race("Both", 15000);
        re1.createRace(Brace1);
        Transport* transport0 = new TwoHumpCamel();
        re1.putVehicle(transport0);
        Transport* transport9 = new Broom();
        re1.putVehicle(transport9);
        Transport* transport8 = new Centaur();
        re1.putVehicle(transport8);
        Transport* transport7 = new Cane();
        re1.putVehicle(transport7);
        re1.printContestants();
        std::string result3 = re1.runRace();
        std::cout << "\nThe winner of this race is " << result3 << "\n\n";
        re1.stopRace();
        // Stop BothRace
                
    } catch (std::runtime_error& e) {
        std::cout << "\nRuntime error occurred..." << std::endl;
        std::cout << e.what() << std::endl;
    }

    
    
    return 0;
}
