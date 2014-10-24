#include "DataStore.h"

DataStore* DataStore::mkdir(std::string name){
	if(m_map.find(name)==m_map.end()){
		DataStore* ds = new DataStore(this, name);
		this->regist(name, ds);
		return ds;
	}else{
		std::cout << name << " has already existed!!" << std::endl;
		return dynamic_cast<DataStore*>(m_map[name]);
	}
};

vector<std::string> DataStore::list(){
	std::map<std::string, IDataBlock*>::iterator it;
	vector<std::string> objs;
	for(it = m_map.begin(); it != m_map.end(); it++){
		objs.push_back(it->first);
	}
	return objs;
};

DataStore::DataStore(DataStore* parent, std::string name){ 
	m_root = parent->m_root;
	m_parent=parent;
	m_path=m_parent->path()+(m_parent->path()=="/"?name:"/"+name);
};


IDataBlock* DataStore::find(std::string name){ 
	vector<std::string> dividedName;
	vector<std::string>::iterator itName;
	boost::split(dividedName, name, boost::is_any_of("/"), boost::token_compress_on);
	DataStore* current = this;
	IDataBlock* db = 0;
	std::cout << "full name " << name  << " size: " << dividedName.size() << std::endl;
	for(itName=dividedName.begin(); itName !=dividedName.end(); itName++){
		std::cout << "get name: " << *itName << std::endl;
		db = current->retrieveObject(*itName);
		if(dynamic_cast<DataStore*>(db)){
			current = dynamic_cast<DataStore*>(db);
		}
		else{
			return db;
		}
		//if(0==current)return 0;
	}
	return current;
};

void DataStore::printTree(){
	std::cout << m_path << std::endl;
	std::map<std::string, IDataBlock*>::iterator it;
	for(it=m_map.begin();it!=m_map.end();it++){
		if(dynamic_cast<DataStore*>(it->second)){
			dynamic_cast<DataStore*>(it->second)->printTree();
		}
		else{
			std::string fullpath = ("/"==m_path)?m_path+it->first:m_path+"/"+it->first;
			std::cout << fullpath << std::endl;
		}
	}
};


