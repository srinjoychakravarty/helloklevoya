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
    uint64_t get_owner_int_reprsnt() const {return owner.value;}
    eosio::name get_pet_name() const {return pet_name;}
    uint64_t get_age() const {return age;}
    eosio::name get_type() const {return type;} 

    // primary key
    uint64_t primary_key() const {return get_id();}

    // macro to indicate all state variables to be stored persistently in pet_t class
    EOSLIB_SERIALIZE(pet_t, (id)(owner)(pet_name)(age)(type))
};

    // eosio::indexed_by <"secondaryindex_identifier", eosio::const_mem_fun<datastructure_used, return_type(must be converted to 64bit int), int_conversion_functioname >
    typedef eosio::multi_index <"pets"_n, pet_t, eosio::indexed_by<"bypetowner"_n, eosio::const_mem_fun<pet_t, uint64_t, &pet_t::get_owner_int_reprsnt>>> pets_table;



#endif