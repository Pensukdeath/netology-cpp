#include <map>
#include <string>
#include <iostream>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept {
        return "Very Big Data String: " + key;
    }
};

class CacheProxyDB : VeryHeavyDatabase {
public:
    explicit CacheProxyDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {}
    std::string GetData(const std::string& key) noexcept {
        if (cache_.find(key) == cache_.end()) {
            std::cout << "Get from real object\n";
            cache_[key] = real_db_->GetData(key);
        }
        else {
            std::cout << "Get from cache\n";
        }
        return cache_.at(key);
    }

private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
};



class OneShotDB : VeryHeavyDatabase 
{
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1) : oneShot_db_(real_object), shots(shots) {}
    std::string GetData(const std::string& key) noexcept 
    {
        if (total_shots < shots)
        {
            total_shots++;
            return(oneShot_db_->GetData(key));
        }
        else
        {
            return("error");
        }
    }
private:
    VeryHeavyDatabase* oneShot_db_;
    size_t shots;
    size_t total_shots{ 0 };
};


int main() {
    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(std::addressof(real_db),2);

    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    return 0;
}