#include"poco.h"


/*
	Poco template
	S: S_ structure which generate by schema
	D: D_ poco structure which wrap S_ object
	T: SqlId struct which determine table

template <typename S, typename D>

struct Poco
{
	S data;
	SqlId T = USERINFO;

	//-----------------------------------------------
	Poco() {}

	Poco ( S & obj ) : data ( obj ) {}
	
	String ToString() const
	{
		return data.ToString();
	}

	virtual void Jsonize ( JsonIO & json );

	// CRUD
	D Create ( Http& http );				// API
	D Edit ( Http& http );					// API
	void Delete ( Http& http );			// API

	Vector<D> Retrieve ( Http& http );		// API
	String RetrieveAsJson ( Http& http );	// API

	//------------------------------------------------
	D GetById ( int id ){

		D rs;
		S x;
		
		try{
			SqlBool where;
			where = ID == id;// condition
			
			SQL *  Select ( SqlAll() ).From ( T ).Where(where).Limit(1);// get only one
		
			
			while ( SQL.Fetch ( x ) ){
				rs = D(x);
				break;
			}
			
		}
		catch(...){
			Cout() << "Error Poco::Get(String id)";
		}
		return  rs;
		
	}

};

template <typename S, typename D>
D Poco<S,D>::GetById(int id)
{
	D  rs;
	S x;
	
	try{
		SqlBool where;
		where = ID == id;// condition
		
		SQL *  Select ( SqlAll() ).From ( this->T ).Where(where);
	
		
		while ( SQL.Fetch ( x ) ){
			rs = D(x);
			break;
		}
		
	}
	catch(...){
		Cout() << "Error poco::Get(int id)";
	}
	return  rs;
}
*/