#ifndef DIFF_DATASTORE_H
#define DIFF_DATASTORE_H

#include "Pulse.h"
#include "IDataBlock.h"
#include <map>
#include <vector>


class DataStore:public IDataBlock{
	public:
		bool regist(std::string name, IDataBlock* data){m_map.insert(make_pair(name, data));}
		IDataBlock* find(std::string name){ return m_map[name] ;}
		vector<std::string> list();
	private:
		std::map<std::string, IDataBlock* > m_map;	
		std::string m_path;


};

typedef boost::shared_ptr<DataStore> DataStorePtr;

vector<std::string> DataStore::list(){
	std::map<std::string, IDataBlock*>::iterator it;
	vector<std::string> objs;
	for(it = m_map.begin(); it != m_map.end(); it++){
		objs.push_back(it->first);
	}
	return objs;
};


#endif
