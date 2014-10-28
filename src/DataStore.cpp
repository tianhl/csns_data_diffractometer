#include "DataStore.h"

DataStorePtr DataStore::mkdir(std::string name){
	if(m_map.find(name)==m_map.end()){
		//DataStore* rawp = new DataStore(DataStorePtr(this), name);
		//DataStorePtr ds(rawp);
		//std::cout << "raw "<< rawp << " sp: " << ds << " spr: " << ds.get() << std::endl;
		//this->regist(name, IDataBlockPtr(ds));
		// errer this->regist(name, IDataBlockPtr(ds.get()));
		DataStorePtr ds(new DataStore(DataStorePtr(this), name));
		this->regist(name, ds);
		return ds;
	}else{
		std::cout << name << " has already existed!!" << std::endl;
		// error here;
		return DataStorePtr(dynamic_cast<DataStore*>(m_map[name].get()));
	}
};

vector<std::string> DataStore::list(){
	std::map<std::string, IDataBlockPtr>::iterator it;
	vector<std::string> objs;
	for(it = m_map.begin(); it != m_map.end(); it++){
		objs.push_back(it->first);
	}
	return objs;
}

DataStore::DataStore(DataStorePtr parent, std::string name){ 
	m_root = parent->m_root;
	m_parent=parent;
	m_path=m_parent->path()+(m_parent->path()=="/"?name:"/"+name);
}

IDataBlockPtr DataStore::retrieveObject(std::string name){ 
	std::cout << __LINE__ << std::endl;
	IDataBlockPtr r = (m_map.find(name)==m_map.end())?IDataBlockPtr():m_map.find(name)->second ;
	std::cout << __LINE__ << " : " << r << std::endl;
	return r;
}

DataStore::~DataStore()
{
	std::cout << __LINE__ << " " << m_path << std::endl;
}

IDataBlockPtr DataStore::find(std::string name){ 
	vector<std::string> dividedName;
	vector<std::string>::iterator itName;
	boost::split(dividedName, name, boost::is_any_of("/"), boost::token_compress_on);
	DataStore* current = (0==name.find("/"))?m_root.get():this;
	IDataBlockPtr db;
	for(itName=dividedName.begin(); itName !=dividedName.end(); itName++){
		if(0==(*itName).size()) continue;
		db = current->retrieveObject(*itName);
		current = dynamic_cast<DataStore*>(db.get());
		if(not current)return db;
	}
	return db;
}

void DataStore::printTree(){
	std::cout << m_path << std::endl;
	std::map<std::string, IDataBlockPtr>::iterator it;
	DataStore* ds;
	for(it=m_map.begin();it!=m_map.end();it++){
		ds = dynamic_cast<DataStore*>(it->second.get());
		if(ds) ds->printTree();
		//else std::cout << ("/"==m_path)?m_path+it->first:m_path+"/"+it->first << std::endl;
	}
};


