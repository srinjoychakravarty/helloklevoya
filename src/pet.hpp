#ifndef PET
#define PET

class [[eosio::table,  eosio::contract("helloklevoya")]] pet_t
{
// private state variables
private:    
    uint64_t _id;
    eosio::name _owner;
    eosio::name _pet_name;
    uint64_t _age;
    eosio::name _type;

    // standard function to construct inline action
    void event_summary(eosio::name caller, std::string msg)
    {
        // action with 4 arguments being prepared
        action
        (
            // active permission of contract itself used as permission level
            permission_level{get_self(), "active"_n},
            // push the action to "this" contract location or a different contract name
            get_self(),
            // name of inline action to forward this construction to
            "notify"_n,
            // tuple of caller and msg
            std::make_tuple(caller, msg)
        ).send();
    }


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
        ) : _id(_id), _owner(_owner), _pet_name(_pet_name), _age(_age), _type(_type) {} 

    // getters
    uint64_t get_id() const {return _id;}
    eosio::name get_owner() const {return _owner;}
    uint64_t get_owner_int_reprsnt() const {return _owner.value;}
    eosio::name get_pet_name() const {return _pet_name;}
    uint64_t get_age() const {return _age;}
    eosio::name get_type() const {return _type;} 

    // primary key
    uint64_t primary_key() const {return get_id();}

    // macro to indicate all state variables to be stored persistently in pet_t class
    EOSLIB_SERIALIZE(pet_t, (_id)(_owner)(_pet_name)(_age)(_type))
};

    // eosio::indexed_by <"secondaryindex_identifier", eosio::const_mem_fun<datastructure_used, return_type(must be converted to 64bit int), int_conversion_functioname >
    typedef eosio::multi_index <"pets"_n, pet_t, eosio::indexed_by<"bypetowner"_n, eosio::const_mem_fun<pet_t, uint64_t, &pet_t::get_owner_int_reprsnt>>> pets_table;



#endif