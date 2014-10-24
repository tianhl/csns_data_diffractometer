#ifndef DIFF_DATASTORE_H
#define DIFF_DATASTORE_H

#include "Pulse.h"
#include "IDataBlock.h"
#include <map>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>



class DataStore:public IDataBlock{
	public:
		DataStore(){m_parent=0;m_root=this;m_path="/";}
		DataStore(DataStore* parent, std::string name);

		std::string path(){return m_path;}
		bool regist(std::string name, IDataBlock* data){m_map.insert(make_pair(name, data));}
		IDataBlock* find(std::string name);
		bool remove(std::string name){m_map.erase(name);}
		DataStore* mkdir(std::string name);

		vector<std::string> list();
		void printTree();
        protected:
		DataStore* m_root;
	private:
		IDataBlock* retrieveObject(std::string name){ return (m_map.find(name)==m_map.end())?0:m_map[name] ;}
	private:
		std::map<std::string, IDataBlock* > m_map;	
		std::string m_path;
		DataStore* m_parent;
};

typedef boost::shared_ptr<DataStore> DataStorePtr;
#endif
