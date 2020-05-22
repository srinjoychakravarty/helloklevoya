#ifndef PET
#define PET

class [[eosio::table,  eosio::contract("helloklevoya")]] pet_t
{
// private state variables
private:    
    uint64_t id;
    eosio::name owner;
    eosio::name pet_name;
    uint64_t age;
    eosio::name type;

public:    
    // default constructor
    pet_t(){}
    // pet_t() = delete;

    // parameterized constructor
    pet_t(
        uint64_t const _id, 
        eosio::name const & _owner, 
        eosio::name const & _pet_name, 
        uint64_t const _age, 
        eosio::name const & _type
        ) : id(_id), owner(_owner), pet_name(_pet_name), age(_age), type(_type) {} 

    // getters
    uint64_t get_id() const {return id;}
    eosio::name get_owner() const {return owner;}
    eosio::name get_pet_name() const {return pet_name;}
    uint64_t get_age() const {return age;}
    eosio::name get_type() const {return type;} 

    // primary key
    uint64_t primary_key() const {return get_id();}

    // macro to indicate all state variables to be stored persistently in pet_t class
    EOSLIB_SERIALIZE(pet_t, (id)(owner)(pet_name)(age)(type))
};

    typedef eosio::multi_index <"pets"_n, pet_t> pets_table;
    // typedef eosio::multi_index <eosio::name("pets"), pet_t> pets_table;


#endif