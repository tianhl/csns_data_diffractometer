#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "nexus/NeXusFile.hpp"
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
using namespace std;

#include "log.h"
#include "config.h"
#include "Pulse.h"


int main(int argc, char *argv[]) {
	if (argc != 2){
		std::cout << "Usage: " << argv[0] << " option.txt" << std::endl;
		return 1;
	}
	std::string configfile(argv[1]);
	Config* fConfig = new Config(configfile);
	std::string samplefile  ; 
	std::string mappingfile  ; 
	samplefile  = fConfig->pString("samplefile") ;  
	mappingfile  = fConfig->pString("mappingfile") ;  
	std::cout << "read sample file:  " << samplefile << std::endl;
	std::cout << "read mapping file: " << mappingfile << std::endl;

	PulsePtr pulse(new Pulse);

	EventPtr evt(new Event);
	evt->setPixelID(2000);
	evt->setTOF(1000);
        pulse->addEvent(evt);

	std::cout << "pixel id: " << pulse->getEvent(0)->getPixelID() << std::endl;
	std::cout << "TOF   id: " << pulse->getEvent(0)->getTOF() << std::endl;

	RawDataPtr raw(new RawData);
	ScintillantPtr sci(new Scintillant);
	raw->setScintillant(sci);
	uint32_t tof = 1234;
	uint32_t x[4] = {1233, 32132, 321321, 659078645};
	uint32_t y[2] = {8, 9};
	HitMapPtr hitmap(new HitMap(tof,x,y));
	sci->addHitMap(hitmap);

	uint32_t id = 97;
	bool b = 0;
	std::cout << "TOF: " << raw->getScintillant()->getHitMap(0)->getTOF() << std::endl;
	std::cout << "get id: " << id << std::endl;
	std::cout << "getX:   " << raw->getScintillant()->getHitMap(0)->getX(id) << std::endl;
	std::cout << "setX:  "<<b << std::endl; 
       	raw->getScintillant()->getHitMap(0)->setX(id,b);
	std::cout << "getX:   " << raw->getScintillant()->getHitMap(0)->getX(id) << std::endl;


}