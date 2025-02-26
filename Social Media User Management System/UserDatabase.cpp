#include "UserDatabase.h"
#include <stack>


// IMPLEMENT THESE
UserDatabase::UserDatabase()
{
	for(size_t i = 0; i < 11 ; i++){
	    _userTable.push_back(NULL);
	}
	_load_factor = 0.75;
    _size = 0;
	_dummy = new UserNode("DumDum");
}

UserDatabase::UserDatabase(size_t s, double load)
{
	for(size_t i = 0; i < s ; i++){
	    _userTable.push_back(NULL);
	}
	_load_factor = load;
    _size = 0;
	_dummy = new UserNode("DumDum");
}

UserDatabase::~UserDatabase()
{
	for(size_t i = 0; i < _userTable.size(); i++){
	    if(_userTable[i] != NULL && _userTable[i] != _dummy){
    	    delete _userTable[i];
	    }
    	_userTable[i] = NULL;
	}
	

	delete _dummy;
    _dummy = NULL;
}

size_t UserDatabase::size() const
{
	return _size;
}

size_t UserDatabase::capacity() const
{
	return _userTable.size();
}

bool UserDatabase::isEmpty() const
{
	int count = 0;
	for(size_t i = 0; i < _userTable.size(); i++){
	    if(_userTable[i] != _dummy && _userTable[i] != NULL){
            count++;
        }
	}
    if(count > 0){
        return false;
    }
    return true;	
}

void UserDatabase::addUser(string username){
    double current_load = static_cast<double>(_size) / _userTable.size();
	if(current_load >= _load_factor){
        resize(2 * _userTable.size() + 1);
    }
    
    int hashindex = hashFunction(username, _userTable.size());

    while(_userTable[hashindex] != NULL && _userTable[hashindex] != _dummy){
            hashindex++;
            if(hashindex >= _userTable.size()){
                hashindex %= _userTable.size();
            }
    }
    
    _userTable[hashindex] = new UserNode(username);
    _size++;	
}

void UserDatabase::removeUser(string username)
{
	int hash_code = hashFunction(username, _userTable.size());
	bool flag = false;
	for(int i = hash_code;;){
	    if(hash_code != 0)
	        if(i == hash_code - 1){
	            break;
	        }
	    else{
	        if(i == _userTable.size() - 1){
	            break;
	        }
	    }
        if (_userTable[i] != NULL && _userTable[i] != _dummy && _userTable[i]->username == username) {
            flag = true;
            UserNode* to_delete = _userTable[i];
            _userTable[i] = _dummy;
            delete to_delete;
            _size--;
            for (size_t k = 0; k < _userTable.size(); k++) {
                if (_userTable[k] != NULL && _userTable[k] != _dummy) {
                    for (size_t j = 0; j < _userTable[k]->follows.size();) {
                        if (_userTable[k]->follows[j] == username) {
                            for(size_t h = j; h < _userTable[k] -> follows.size() - 1; ++h){
                                _userTable[k] -> follows[h] = _userTable[k] -> follows[h + 1];
                            }
                            _userTable[k] -> follows.pop_back();
                            break;
                        }
                        else{
                            j++;
                        }
                    }
                }
            }
            break;
    	}
        i = (i + 1) % _userTable.size();
	}
	
	if(!flag){
	    throw UserDoesNotExistException(username);
	}
}

UserNode* UserDatabase::getUser(string username) const
{
    bool flag = false;
    for(size_t i = 0; i < _userTable.size(); i++){
        if (_userTable[i] != NULL && _userTable[i] != _dummy && _userTable[i] -> username == username){
            flag = true;
            return _userTable[i];
            break;
        }
    }
    if(!flag){
        throw UserDoesNotExistException(username);
    }
    
}

void UserDatabase::resize(size_t size)
{
	vector<UserNode*> old_one = _userTable;
    _userTable = vector<UserNode*>(size, NULL);
    _size = 0;
	
	for(size_t k = 0; k < old_one.size(); k++){
	    if(old_one[k] != NULL && old_one[k] != _dummy){
	        addUser(old_one[k] -> username);
	        delete old_one[k];
	    }
	}
}

void UserDatabase::follow(string username1, string username2)
{
	if(!userExists(username1)){
	    throw UserDoesNotExistException(username1);
	}
	if(!userExists(username2)){
	    throw UserDoesNotExistException(username2);
	}
	
	UserNode* user1 = getUser(username1);
	UserNode* user2 = getUser(username2);
	
	bool flag = false;
	for(size_t i = 0; i < user1 -> follows.size(); i++){
	    if(user1 -> follows[i] == username2){
	        flag = true;
	        break;
	    }
	}
	
	if(flag){
	    RedundantActionException(username1, username2, true);
	}
	
	user1 -> follows.push_back(username2);
}

void UserDatabase::unfollow(string username1, string username2)
{
	if(!userExists(username1)){
	    throw UserDoesNotExistException(username1);
	}
	if(!userExists(username2)){
	    throw UserDoesNotExistException(username2);
	}
	
	UserNode* user1 = getUser(username1);
	UserNode* user2 = getUser(username2);
	
	bool flag = false;
	for(size_t i = 0; i < user1 -> follows.size(); i++){
	    if(user1 -> follows[i] == username2){
	        flag = true;
	        break;
	    }
	}
	
	if(!flag){
	    RedundantActionException(username1, username2, false);
	}
	
    for(size_t i = 0; i < user1 -> follows.size(); i++){
        if(user1 -> follows[i] == username2){
            for(size_t j = i; j < user1 -> follows.size() - 1; ++j){
                user1 -> follows[j] = user1 -> follows[j + 1];
            }
            user1 -> follows.pop_back();
            break;
        }
    }
}


bool UserDatabase::userExists(string username) const
{
    for(size_t i = 0; i < _userTable.size(); i++){
        if (_userTable[i] != NULL && _userTable[i] != _dummy && _userTable[i] -> username == username){
            return true;
        }
    }
    
	return false;
}

bool UserDatabase::userFollows(string username1, string username2) const
{
	if(!userExists(username1)){
	    throw UserDoesNotExistException(username1);
	}
	if(!userExists(username2)){
	    throw UserDoesNotExistException(username2);
	}
	
	UserNode* user1 = getUser(username1);
	UserNode* user2 = getUser(username2);
	
	bool flag = false;
	for(size_t i = 0; i < user1 -> follows.size(); i++){
	    if(user1 -> follows[i] == username2){
	        flag = true;
	        break;
	    }
	}
    if(flag){
        return true;
    }
    return false;
}

size_t UserDatabase::userFollowerCount(string username) const
{
	if(!userExists(username)){
	    throw UserDoesNotExistException(username);
	}
    
    size_t count = 0;
    
    for(size_t i = 0; i < _userTable.size(); i++){
        if(_userTable[i] != NULL && _userTable[i] != _dummy){
            UserNode* current =  _userTable[i];
            for(size_t k = 0; k < current -> follows.size(); k++){
                if(current -> follows[k] == username){
                    count++;
                }
            }
        }
    }
    
    return count;
}

size_t UserDatabase::userFollowsCount(string username) const
{
	if(!userExists(username)){
	    throw UserDoesNotExistException(username);
	}
	
    UserNode* user = getUser(username);
    
    return user -> follows.size();
}

vector<string> UserDatabase::getUserList() const
{
	vector<string> result_list;
    for(size_t i = 0; i < _userTable.size(); i++){
        if (_userTable[i] != NULL && _userTable[i] != _dummy){
            result_list.push_back(_userTable[i] -> username);
        }
    }
	
	return result_list;
}

void UserDatabase::printAdjacencyMatrix() const
{
	for(size_t i = 0; i < _userTable.size(); i++){
	    if(_userTable[i] != NULL &&_userTable[i] != _dummy){
    	    UserNode* user1 = _userTable[i];
    	    for(size_t j = 0; j < _userTable.size(); j++){
    	        if(_userTable[j] != NULL &&_userTable[j] != _dummy){
        	        UserNode* user2 = _userTable[j];
        	        if(userFollows(user1 -> username, user2 -> username)){
        	            std::cout << 1 << " ";
        	        }
        	        else{
        	            std::cout << 0 << " ";
        	        }
    	        }
    	    }
    	    std::cout << endl;
	    }
	}
}

int UserDatabase::BFS(string username1, string username2, bool printPath)
{
	if(!userExists(username1)){
	    throw UserDoesNotExistException(username1);
	}
	if(!userExists(username2)){
	    throw UserDoesNotExistException(username2);
	}
	
	queue<UserNode*> usage;
	vector<UserNode*> visited;
	
	UserNode* beginning = getUser(username1);
	
	usage.push(beginning);
	visited.push_back(beginning);
	int purpose = 0;
    bool dedected = false;


    while(!usage.empty()){
        
        int how_many = usage.size();
        
        for(int k = 0; k < how_many; k++){
            UserNode* front_one = usage.front();
            usage.pop();
            
            if(front_one -> username == username2){
                dedected = true;
                break;
            }
    
    	    for(size_t i = 0; i < front_one -> follows.size(); i++){
    	        UserNode* cobay = getUser(front_one -> follows[i]);
    	        bool flag = false;
    	        for(size_t j = 0; j < visited.size(); j++){
    	            if(cobay == visited[j]){
    	                flag = true;
    	            }
    	        }
    	        
    	        if(!flag){
                	usage.push(cobay);
    	            visited.push_back(cobay);
    	        }
    	    }
        }
        
    	if(dedected){
    	    break;
    	}
    	
        purpose++;
    }
    
    if(!dedected){
        if(printPath){
            for(size_t i = 0; i < visited.size(); i++){
                std::cout << visited[i] -> username << " ";
            }
            std::cout << endl;
            return -1;
        }
        return -1;
    }
    
    if(printPath == false){
        return purpose;
    }
    
    if(printPath == true){
        for(size_t i = 0; i < visited.size(); i++){
            if(visited[i] -> username == username2){
                std::cout << visited[i] -> username << " ";
                break;
            }
            std::cout << visited[i] -> username << " ";
        }
        std::cout << endl;
        return purpose;
    }
}

int UserDatabase::DFS(string username1, string username2, bool printPath)
{
	if(!userExists(username1)){
	    throw UserDoesNotExistException(username1);
	}
	if(!userExists(username2)){
	    throw UserDoesNotExistException(username2);
	}
	
	std::stack<UserNode*> usage;
	vector<UserNode*> visited;
	
	UserNode* beginning = getUser(username1);
	
	usage.push(beginning);
	visited.push_back(beginning);
	
    bool dedected = false;
    
    while(!usage.empty()){
        
        UserNode* top_one = usage.top();
        
        if(top_one -> username == username2){
            dedected = true;
            break;
        }
        
        bool all_visited = true;
        for(size_t i = 0; i < top_one -> follows.size(); i++){
            UserNode* current = getUser(top_one -> follows[i]);
	        bool flag = false; 
	        for(size_t j = 0; j < visited.size(); j++){
	            if(current == visited[j]){
	                flag = true;
	            }
	        }
	        
	        if(!flag){
	            usage.push(current);
            	visited.push_back(current);
            	all_visited = false;
            	break;
	        }
        }
        
        if(all_visited){
            usage.pop();
        }
    }
    
    
    if(!dedected){
        if(printPath){
            for(size_t i = 0; i < visited.size(); i++){
                std::cout << visited[i] -> username << " ";
            }
            std::cout << endl;
            return -1;
        }
        return -1;
    }
    
    if(printPath){
        for(size_t i = 0; i < visited.size(); i++){
            std::cout << visited[i] -> username << " ";
        }
        std::cout << endl;
        return usage.size() - 1;
    }
    
    return usage.size() - 1;
}

double UserDatabase::averageBFS() {
    vector<string> hanging = getUserList();

    double sum = 0.0;
    double pair = 0.0;

    for(size_t k = 0; k < hanging.size() ; k++){
        string user1 = hanging[k];
        for(size_t l = 0; l < hanging.size(); l++){
            if(k != l){
            string user2 = hanging[l];
            
            int bfs = BFS(user1, user2, false);
            if(bfs != -1){
                sum += static_cast<double>(bfs);
                pair++;
            }
            }
        }
    }

    if(pair > 0){
        return sum / pair;
    }
     else{
         return 0.0;
     }
}


double UserDatabase::averageDFS()
{
    vector<UserNode*> hanging;

    for(size_t i = 0; i < _userTable.size(); i++){
        if(_userTable[i] != NULL && _userTable[i] != _dummy){
            hanging.push_back(_userTable[i]);
        }
    }

    if(hanging.size() < 2){
        return 0.0;
    }

    double sum = 0.0;
    double pair = 0.0;

    for(size_t k = 0; k < hanging.size(); k++){
        UserNode* user1 = hanging[k];
        for(size_t l = 0; l < hanging.size(); l++){
            if(k!=l){
            UserNode* user2 = hanging[l];

            int dfs = DFS(user1->username, user2->username, false);
            if(dfs != -1){
                sum += static_cast<double>(dfs);
                pair++;
                
            }
                
            }
        }
    }

    if(pair > 0){
        return sum / pair;
    }
     else{
         return 0.0;
     }
}

vector<string> UserDatabase::getSharedNeighbourhood(string username1, string username2, size_t k)
{
    if(!userExists(username1)){
	    throw UserDoesNotExistException(username1);
	}
	if(!userExists(username2)){
	    throw UserDoesNotExistException(username2);
	}
	
	vector<string> storage = getUserList();
	vector<string> smiley;
	
	for(size_t t = 0; t < storage.size(); t++){
	    string denek = storage[t];

	    int distance1 = BFS(denek, username1, false);
	    int distance2 = BFS(denek, username2, false);

	    if(distance1 < k && distance2 < k){
	        smiley.push_back(denek);
	    }
	}
	
	return smiley;

}

// ADD YOUR HELPER FUCTIONS HERE

