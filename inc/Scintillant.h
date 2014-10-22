#ifndef DIFF_SCINTILLANT_H
#define DIFF_SCINTILLANT_H

#include <stdlib.h>
// how to get binary string
//#include <bitset>
//bitset<32> binary_orig(uint32_orig);
#include <boost/shared_ptr.hpp>
using namespace std;


class HitMap{
	public:
		HitMap(uint32_t tof, uint32_t *x, uint32_t *y) { m_tof = tof; m_x = x; m_y = y; }
		const uint32_t getTOF() const { return m_tof; }
		const bool getX(uint32_t id) const{ return bool((m_x[id/32]>>(id%32))&0x1); }
		const bool getY(uint32_t id) const{ return bool((m_y[id/32]>>(id%32))&0x1); }
		void setX(uint32_t id, bool bv){ bv?(m_x[id/32]|=(1<<(id%32))):(m_x[id/32]&=(~(1<<(id%32)))); }
		void setY(uint32_t id, bool bv){ bv?(m_y[id/32]|=(1<<(id%32))):(m_y[id/32]&=(~(1<<(id%32)))); }
	private:
		uint32_t m_tof;
		uint32_t *m_x;
		uint32_t *m_y;

};


typedef boost::shared_ptr<HitMap> HitMapPtr;
typedef vector<HitMapPtr> HitMapCol;
typedef HitMapCol::iterator HitColIter;


class Scintillant{
	public:
		const HitMapCol getHitMapCol() const {return m_hitmapcol;}
		void setHitMapCol(HitMapCol hitmapcol) {m_hitmapcol = hitmapcol; }
		void clearHitMapCol() {m_hitmapcol.clear(); }

		const HitMapPtr getHitMap(uint32_t index) const { return m_hitmapcol.at(index); }
		void addHitMap(HitMapPtr hitmap) { m_hitmapcol.push_back(hitmap); }


		const uint32_t getGroup() const {return m_group; }
		void setGroup(uint32_t group) {m_group = group; } 

		const uint32_t getModule() const {return m_module; }
		void setModule(uint32_t module) {m_module = module; } 
	private:
		uint32_t m_group;
		uint32_t m_module;
		HitMapCol m_hitmapcol;
};

typedef boost::shared_ptr<Scintillant> ScintillantPtr;

#endif
