#ifndef DIFF_PULSE_H
#define DIFF_PULSE_H

#include <stdlib.h>
#include "Event.h"
#include "RawData.h"
#include <boost/shared_ptr.hpp>
#include <vector>
#include "IDataBlock.h"
using namespace std;

class Pulse:public IDataBlock{
	public:
		const uint64_t getPulseID() const {return m_pulseid; }
		void setPulseID(uint64_t pulseid) {m_pulseid = pulseid; }

		const uint32_t getTimeSec() const {return m_timesec; }
		void setTimeSec(uint32_t timesec) {m_timesec = timesec; }

		const uint32_t getTimeSub() const {return m_timesub; }
		void setTimeSub(uint32_t timesub) {m_timesub = timesub; }

		const RawDataPtr getRawData() const {return m_rawdata; }
		void setRawData(RawDataPtr rawdata) {m_rawdata = rawdata; }

		const EvtCol getEvtCol() const {return m_evtcol; }
		void setEvtCol(EvtCol evtcol) {m_evtcol = evtcol; }
		void clearEvtCol() {m_evtcol.clear(); }

		const EventPtr getEvent(uint32_t index) const {return m_evtcol.at(index); }
		void addEvent(EventPtr evt) {m_evtcol.push_back(evt); }

	private:
		uint64_t m_pulseid;	
		uint32_t m_timesec;
		uint32_t m_timesub;
		RawDataPtr m_rawdata;
		EvtCol     m_evtcol;

};

typedef boost::shared_ptr<Pulse> PulsePtr;
typedef vector<PulsePtr> PulseCol;
typedef PulseCol PulseColIter;

#endif
