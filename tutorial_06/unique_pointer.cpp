/**
 *
 *
 *           @name  unique_pointer.cpp
 *          @brief  Template class implementing unique pointer semantics for arbitrary types
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *        @version  1.0
 *           @date  11/20/2014 (08:39:00 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *
 *
 */

#include <iostream>
#include <iomanip>
#include <typeinfo>

using namespace std;


template<class T>
class UniquePointer {
public:

    // TODO: complete the implementation
    // HINT: do not lose information.

    /// @brief Create a unique pointer to hold the instance passed.
	///
	/// This function just assigns the passed `T *obj` pointer to the local `T* _obj`.
	/// Then assigns to `_index` the value `Index` and _then_ increases the latter by 1.
    UniquePointer( T* obj ) : _obj( obj ), _index( Index++ ) {
		std::cerr << " > constructor: _index = " << _index <<
			" Index = " << Index << std::endl;
	};

    // TODO: complete the implementation, implement the _semantics_ of a unique pointer!

    /// @brief "Move" the instance into a new instance of the unique pointer type.
	/// 
	/// "move" = copies the address of the old `_obj` and nullifies it.
    UniquePointer( UniquePointer& uptr ) : _obj( uptr._obj ),  _index(Index++) {
		std::cerr << " > copy constructor: _index = " << _index <<
			" Index = " << Index << std::endl;

		// nullify the objet I copiated from
		uptr._obj = nullptr;
	};

	/// @brief Forbid the default copy constructor explicitly using __C++11__ features.
	///
	/// In this way, one is forced to use the user-defined copy constructor which allows
	/// the passed argument to be edited (and hence his `._obj` field to be nullified).
    UniquePointer( const UniquePointer& uptr ) = delete;

    /// @brief destructor that cleans up if necessary, also notifies about actions taken
    ~UniquePointer() {
        std::cout << "Deleting _index " << _index << " of class "
			<< typeid(_obj).name() << std::endl;

    	// TODO complete the implementation
    	if ( _obj != nullptr )
        {
            std::cout << "-> deleting object" << std::endl;
            delete _obj;
        }
        else
        {
            std::cout << "-> object already destroyed" << std::endl;
        }

		// @attention When you delete this object, his destructor will be called!
		// So if two instances of `UniquePointer` point to the same object (?)
//		delete _obj;
//		std::cout << "_obj (address) value " << _obj << std::endl;
    };

    /// assignment operator for unique pointer type 
    // TODO: is it needed? is it clean?
	
	/// @brief Assignment operator
	///
	/// This doesn't increase neither `_index` or `Index`.
    void
    operator=(UniquePointer& uptr) // = delete;
    {
	    // TODO: implement _clean_ assignment, implementing unique pointer semantics consistently

		std::cerr << "assignment operator" << std::endl;

		/// Notify the user he's deleting an existing object. This will also notify
		/// if the current `_obj` has been deleted since after `delete _obj` his address
		/// is _not_ set to `nullptr`. 
		if ( _obj != nullptr )
		{
			std::cerr << "Index " << Index << " of class " << typeid( _obj ).name() << 
				" >>> Deleting object upon new assignment!" << std::endl;
		}
		else
		{
			std::cerr << "Index " << Index << " of class " << typeid( _obj ).name() << 
				" >>> Inserting object upon new assignment!" << std::endl;
		}

		/// Copy the object.
		_obj = uptr._obj;
		/// Nullify the old object
		uptr._obj = nullptr;
    };

    // TODO implement function(s) to give convenient access to the instance
 
    /// @brief Dereference to work with the instance.
	///
	/// Just returns an (editable) pointer to the `_obj`.
    T*
    operator->() {
		return _obj;
	};

    /// @brief onst dereference to work with instance the in const-contexts
	///
	/// Again as the normal dereference, but making sure the pointer cannot be changed.
    /// Therefore, return a const pointer AND make the function const (so that it cannot 
	/// change the internal state of the UniquePointer instance).
	const T*
	operator->() const {
		return _obj;
	};

	void
	printAddress () const {
		std::cout << _obj << std::endl;
	};
private:

    /// the instance all this fuss is about
    T*     _obj;
    /// an index to keep track of the destructor calls
    size_t _index;

    /// counter to identify all instances of this unique pointer type
    static size_t Index;
};

// initilizes the class-wide index counter
template<class T>
size_t UniquePointer<T>::Index = 0lu;


/**
 * Simple test class that does not really matter.
 *
 * @attention In C++ `struct` and `class` are the same!
 */
struct TestClass
{
    TestClass() {
        std::cout << "Creating instance of TestClass" << std::endl;
    };

    ~TestClass() {
        std::cout << "Deleting instance of TestClass" << std::endl;
    };

    void
    doSomething() const {
        std::cout << "Doing something" << std::endl;
    };
};

int main() {

// TODO remove comment (after completing implementation of UniquePointer class), run the example and interpret

    typedef UniquePointer<TestClass> PtrType;

    std::cout << "test case 1: deleting in inner context" << std::endl;
    {
        PtrType uptr1( new TestClass() );
        {
//			uptr1.printAddress();

            PtrType uptr2(uptr1);
			// now the `_obj` field of `uptr1` is 0
//			uptr1.printAddress();

//			uptr2.printAddress();

            const PtrType& uptr2_cref = uptr2;
//			uptr2.printAddress();
//			uptr2_cref.printAddress();

			// After this assignment `uptr2._obj` is equal to `nullptr` so it will not be
			// destroyed because of the test.

            //TODO uncomment and make this work by providing the necessary operators.
			uptr2->doSomething();
			uptr2_cref->doSomething();
        }
    }

    std::cout << std::endl << "test case 2: deleting in outer context" << std::endl;
    {
        PtrType uptr3(nullptr);
        {
            PtrType uptr4(new TestClass());
            // TODO forbid the assignment operator and think about how this case can still be made work

			// Now `uptr3` contains the address of `TestClass()` and `uptr4._obj = nullptr`
            uptr3 = uptr4;
        }
    }

    return 0;
}


