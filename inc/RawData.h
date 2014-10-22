#ifndef DIFF_RAWDATA_H
#define DIFF_RAWDATA_H

#include <stdlib.h>
#include <boost/shared_ptr.hpp>
#include "Scintillant.h"
using namespace std;


class RawData{
	public:
		const ScintillantPtr getScintillant() const {return m_scintillant; }
		void setScintillant(ScintillantPtr scintillant) {m_scintillant = scintillant; }
	private:
		ScintillantPtr m_scintillant;
};

typedef boost::shared_ptr<RawData> RawDataPtr;
#endif
