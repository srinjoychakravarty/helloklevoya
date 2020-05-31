#include "helloklevoya.hpp"

void helloklevoya::addpet(uint64_t const _id, eosio::name const & _owner, eosio::name const & _pet_name, uint64_t const _age, eosio::name const & _type)
{

  // only authorized user can modify their own pet
  require_auth(_owner);
  
  // Type: custom eos table > pets_table 
  // Table Name: pets
  // 1st Param: table in current smart contract 
  // 2nd Param: scope of table is global i.e. anyone can access
  pets_table pets(get_self(), get_self().value);
 
  // searches table for id (primary key)
  auto pet_iterator = pets.find(_id);

  // ensures same pet id doesn't exist in table before allowing insertion
  eosio::check(pet_iterator == pets.end(), "Pet ID already exists...can't register again!");
 
  // 1st Param: payer of RAM
  // 2nd Param: lambda function which sets table entry type to pet_t
  pets.emplace(get_self(), [&](auto & entry) 
  {
    entry = pet_t(_id, _owner, _pet_name, _age, _type);
  });
}

void helloklevoya::updatepet(uint64_t const _id, eosio::name const & _owner, eosio::name const &  _pet_name, uint64_t const _age, eosio::name const & _type)
{
  pets_table pets(get_self(), get_self().value);
  auto pet_iterator = pets.find(_id);

  // ensures pet exists in table before allowing update
  eosio::check(pet_iterator != pets.end(), "Non-existant Pet ID can't be updated");

  // allows the actual owner of the pet to update
  require_auth(pet_iterator -> get_owner());

  // prevents pets getting younger with passage of time
  eosio::check(_age >= pet_iterator -> get_age(), "Pet cannot get younger over time");

  // if found iterator id from pets table is passed in as additional first argument
  pets.modify(pet_iterator, get_self(), [&](auto & entry) 
  {
    entry = pet_t(_id, _owner, _pet_name, _age, _type);
  });       
}

void helloklevoya::deletepet(uint64_t const _id)
{
  pets_table pets(get_self(), get_self().value);
  auto pet_iterator = pets.find(_id);
  eosio::check(pet_iterator != pets.end(), "Non-existant Pet ID can't be deleted");
  require_auth(pet_iterator -> get_owner());
  pets.erase(pet_iterator);
}

void helloklevoya::listpet(uint64_t const _id)
{
  pets_table pets(get_self(), get_self().value);
  auto pet_iterator = pets.find(_id);
  eosio::check(pet_iterator != pets.end(), "Non-existant Pet ID can't be displayed");
  require_auth(pet_iterator -> get_owner());
  eosio::print("Pet ID: ", _id, " belongs to ", pet_iterator -> get_pet_name(), " who is a ", pet_iterator -> get_type(), " pokémon aged ", pet_iterator -> get_age(), "!");
}

void helloklevoya::ownedpetsby(eosio::name const & _owner)
{
  require_auth(_owner);
  pets_table pets(get_self(), get_self().value);
  // use secondary index to sort table by owner
  auto pets_by_owner = pets.get_index<"bypetowner"_n>();
  // find iterator for first pet by owner's 64 bit integer value (inclusive)
  auto first_pet_iterator = pets_by_owner.lower_bound(_owner.value); 
  // iterator goes past last pet memory location belonging to owner
  auto last_pet_iterator = pets_by_owner.upper_bound(_owner.value); 
  // for loop print pets for all pet memory locations belonging to owner
  for(auto i = first_pet_iterator; i != last_pet_iterator; ++i)
  {
    eosio::print( _owner, " trains ", i -> get_type(), " pokémon ",  i -> get_pet_name(), "\n");
  } 
}