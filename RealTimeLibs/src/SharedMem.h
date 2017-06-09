/*
 * SharedMem.h
 *
 *  Created on: Jun 28, 2016
 *      Author: mojtaba
 */

#ifndef SHAREDMEM_H_
#define SHAREDMEM_H_

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

using namespace boost::interprocess;
typedef allocator<char, managed_shared_memory::segment_manager>   CharAllocator;
typedef basic_string<char, std::char_traits<char>, CharAllocator> ShmString;
typedef allocator<ShmString, managed_shared_memory::segment_manager> ShmStringAllocator;
typedef deque<ShmString, ShmStringAllocator> ShmStringDeque;
////  manage the mode that shared mem will be open
enum setupMode{client,server};
enum Status{initialized,ready,failed};

// configure allocator for saving the deque object in shared memory, we need to use the boost IPC container for that
namespace Comms
{



class SharedMem {
public:
	SharedMem(std::string name="EventArea",std::string qName="EventQ",size_t size=9999999,bool withLock=true);
	virtual ~SharedMem();

	const std::string& getName();

	int   setUp(setupMode mode=server);

	void setName(const std::string& name);
	const std::string& getQueueName() const;
	void setQueueName(const std::string& queueName);
	void pushBackString(std::string data);
	void safePushBackString(std::string data);
	void safePushFrontString(std::string data);
	void pushFrontString(std::string data);
	std::string popFrontString();
	std::string popBackString();
	std::string getData(size_t index=0);
	int  getQueueSize();
	std::string safePopFrontString();
	std::string safePopBackString();
	std::string safeGetData(size_t index=0);
	int  safeGetQueueSize();
	Status getStatus() const;
	void setStatus(Status status);
	bool isWithLock() const;
	void setWithLock(bool withLock);
	void removeSharedArea();

	size_t getSize() const {
		return this->size;
	}

	void setSize(size_t size) {
		this->size = size;
	}

	//void

private :
	std::string name;
	ShmStringDeque *sharedDeque;
	std::string queueName;
	managed_shared_memory observerSegment;
	bool withLock;
	Status status;
	named_mutex * areaMutex;
	size_t size;
};

inline SharedMem::SharedMem(std::string name,std::string qName,size_t size,bool withLock)
{

	sharedDeque=0;
	areaMutex=0;
	//charallocator=0;
	this->setName(name);
	this->setQueueName(qName);
	this->status=initialized;
	this->withLock=withLock;
	this->size=size;
}
//////
inline  SharedMem::~SharedMem()
{
	shared_memory_object::remove(this->name.c_str());

}
/////
inline void SharedMem::removeSharedArea()
{
	shared_memory_object::remove(this->name.c_str());
}
////
inline const std::string& SharedMem::getName()
{
		return name;
}
//////
inline int SharedMem::setUp(setupMode mode)  // setup shared memory segment, and allocate the object for read and write
{
	if (mode==server)
	{
		try
		{
			shared_memory_object::remove(this->getName().c_str()); // remove it if it is already created before
			this->observerSegment=managed_shared_memory(create_only, this->getName().c_str(),this->getSize());
			const CharAllocator charallocator (observerSegment.get_segment_manager());
			const ShmStringAllocator stringInst(observerSegment.get_segment_manager());
			this->sharedDeque = observerSegment.construct<ShmStringDeque>(this->getQueueName().c_str())(stringInst);
			/// create the mutex also for locking
			named_mutex::remove((this->getName()).c_str());
			this->areaMutex=new named_mutex(open_or_create, (this->getName()).c_str());
			this->setStatus(ready);
			return 0;
		}
		catch(boost::interprocess::interprocess_exception &ex){
		            std::cout << "The Error happened in  shared memory setup: "<<"\n";
		            this->setStatus(failed);
		            return -1;
		}

	}
	else if (mode==client)
	{
		try
		{
			this->observerSegment=managed_shared_memory(open_only, this->getName().c_str());
			// find and load related queue
			this->sharedDeque = observerSegment.find<ShmStringDeque>(this->getQueueName().c_str()).first;
			//this->sharedDeque = segment.find<ShmStringVector>("MyVector").first;
			this->setStatus(ready);
			/// create the mutex
			this->areaMutex=new named_mutex(open_only, (this->getName()).c_str());
			//this->areaMutex=new named_mutex(open_or_create, (this->getName()).c_str());
			return 0;
		}
		catch (boost::interprocess::interprocess_exception &ex)
		{
			std::cout << "The Error happened in  shared memory setup: "<<"\n";
			this->setStatus(failed);
			return -1;
		}

	}
	else
		// no other mode exist now, will extended in future
		return -1;

}

///
inline void SharedMem::setName(const std::string& name)
{
	this->name = name;
}
/////
inline const std::string& SharedMem::getQueueName() const {
	return queueName;
}
//////
inline void SharedMem::setQueueName(const std::string& queueName) {
	this->queueName = queueName;
}
//////
inline Status SharedMem::getStatus() const {
	return status;
}
//////
inline void SharedMem::setStatus(Status status) {
	this->status = status;
}
//////
inline bool SharedMem::isWithLock() const {
	return withLock;
}
////
inline void SharedMem::setWithLock(bool withLock) {
	this->withLock = withLock;
}

inline std::string SharedMem::popFrontString()
//////
{
	if (! this->sharedDeque->empty())
	{
		//const CharAllocator charallocator (observerSegment.get_segment_manager());
		//ShmString tempString(charallocator);
		//tempString= this->sharedDeque->front();
		//return std::string(tempString.begin(),tempString.end());
		//std::cout<<"reading from shared memory\n";
		std::string s1= std::string(this->sharedDeque->front().begin(),this->sharedDeque->front().end());
		//std::cout<<s1;
		this->sharedDeque->pop_front();
		return s1;

	}
	else
		return "";
}
////
inline std::string SharedMem::popBackString()
{
	if (! this->sharedDeque->empty())
	{
		const CharAllocator charallocator (observerSegment.get_segment_manager());
		ShmString tempString(charallocator);
		tempString=this->sharedDeque->back();
		this->sharedDeque->pop_back();
		return std::string(tempString.begin(),tempString.end());
		//return s;
		//return "---";
	}
	else
		return "";
}
////
inline std::string SharedMem::getData(size_t index)
{
	if ( this->sharedDeque->size() > index)
		{
			const CharAllocator charallocator (observerSegment.get_segment_manager());
			ShmString tempString(charallocator);
			tempString=this->sharedDeque->at(index);
			return std::string(tempString.begin(),tempString.end());
			//return "---";
		}
	else
			return "";
}

inline int  SharedMem::safeGetQueueSize()
{
	{scoped_lock<named_mutex> lock(*areaMutex);
	return this->sharedDeque->size();}
}
inline std::string SharedMem::safePopFrontString()
{
	{scoped_lock<named_mutex> lock(*areaMutex);
	return this->popFrontString();}
}
inline std::string SharedMem::safePopBackString()
{
	{scoped_lock<named_mutex> lock(*areaMutex);
	return this->popBackString();}
}
inline std::string SharedMem::safeGetData(size_t index)
{
	{scoped_lock<named_mutex> lock(*areaMutex);
	return this->getData(index);}
}

inline int  SharedMem::getQueueSize()
{
	return this->sharedDeque->size();
}

inline void SharedMem::pushBackString(std::string data)
{
	const CharAllocator charallocator (observerSegment.get_segment_manager());
	ShmString tempString(charallocator);
	tempString=data.c_str();
	this->sharedDeque->push_back(tempString);
}
inline void SharedMem::safePushFrontString(std::string data)
{

	const CharAllocator charallocator (observerSegment.get_segment_manager());
	ShmString tempString(charallocator);
	tempString=data.c_str();
	{scoped_lock<named_mutex> lock(*areaMutex);
	this->sharedDeque->push_back(tempString);}
}
inline void SharedMem::pushFrontString(std::string data)
{
	const CharAllocator charallocator (observerSegment.get_segment_manager());
	ShmString tempString(charallocator);
	tempString=data.c_str();
	this->sharedDeque->push_front(tempString);
}
inline void SharedMem::safePushBackString(std::string data)
{

	const CharAllocator charallocator (observerSegment.get_segment_manager());
	ShmString tempString(charallocator);
	tempString=data.c_str();
	{scoped_lock<named_mutex> lock(*areaMutex);
	this->sharedDeque->push_front(tempString);}
}

}
#endif /* SHAREDMEM_H_ */
