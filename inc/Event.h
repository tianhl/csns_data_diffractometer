#ifndef DIFF_EVENT_H
#define DIFF_EVENT_H

#include <stdlib.h>
#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "IDataBlock.h"
using namespace std;


class Event:public IDataBlock{
	public:
		const uint64_t getPixelID() const {return m_pixelid; }
		void setPixelID(uint64_t id) { m_pixelid = id; }

		const uint64_t getTOF() const {return m_tof; }
		void setTOF(uint64_t tof) { m_tof = tof; }
	private:
		uint64_t m_pixelid;
		uint32_t m_tof;
		// pixelcollection?
};

typedef boost::shared_ptr<Event> EventPtr;
typedef vector<EventPtr> EvtCol;
typedef typename vector<EventPtr>::iterator EvtColIter;


#endif
