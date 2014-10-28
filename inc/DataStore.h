#ifndef DIFF_DATASTORE_H
#define DIFF_DATASTORE_H

#include "Pulse.h"
#include "IDataBlock.h"
#include <map>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>


class DataStore;
typedef boost::shared_ptr<DataStore> DataStorePtr;
typedef boost::shared_ptr<IDataBlock> IDataBlockPtr;

class DataStore:public IDataBlock{
	public:
		DataStore(){m_parent=DataStorePtr();m_root=DataStorePtr(this);m_path="/";}
		DataStore(DataStorePtr parent, std::string name);

		~DataStore();

		std::string path(){return m_path;}
		bool regist(std::string name, IDataBlockPtr data){m_map.insert(make_pair(name, data));}
		IDataBlockPtr find(std::string name);
		bool remove(std::string name){m_map.erase(name);}
		DataStorePtr mkdir(std::string name);

		vector<std::string> list();
		void printTree();

        protected:
		DataStorePtr m_root;
	private:
		IDataBlockPtr retrieveObject(std::string name);
	private:
		std::map<std::string, IDataBlockPtr> m_map;	
		std::string m_path;
		DataStorePtr m_parent;
};

#endif
