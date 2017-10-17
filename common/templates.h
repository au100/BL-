//==============================================================================
#ifndef TEMPLATES_H
#define TEMPLATES_H
//==============================================================================
//		Andrei Ushakov
//==============================================================================
template <class T>
class TFilePtr
{
   private:
      T                 handle;
public:
                        TFilePtr(T _handle)
                           : handle(_handle)
                        {
                        }
      T                 Handle()
                        {
                           return handle;
                        }
      operator          T()
                        {
                           return handle;
                        }
};
//==============================================================================
// autodestruct heap memory handle pointer for class and MemPtr
//==============================================================================
template<class T> class TMemPtr
{
   private:
      T*                pointer;
   public:
                        TMemPtr(T *_pointer = Q_NULLPTR)
                           : pointer(_pointer)
                        {
                        }
                       ~TMemPtr()
                        {
                           if(pointer != Q_NULLPTR)
                              delete pointer;
                        }
      operator          T*()
                        {
                           return pointer;
                        }
      T*                operator =(T* _pointer)
                        {
                           return pointer = _pointer;
                        }
      T&                operator [](int i)
                        {
                           return pointer[i];
                        }
      bool              operator !() const
                        {
                           return pointer == Q_NULLPTR;
                        }
      T*                get()
                        {
                           return pointer;
                        }
      void              reset(T* _pointer = Q_NULLPTR)
                        {
                           if(pointer != Q_NULLPTR)
                              delete pointer;
                           pointer = _pointer;
                        }
      T*                release()
                        {
                           T* tmp = pointer;
                           pointer = 0;
                           return tmp;
                        }
};
//==============================================================================
template<class T>
class TClassPtr : public TMemPtr<T>
{
   public:
                        TClassPtr(T *_pointer = Q_NULLPTR)
                           : TMemPtr<T>(_pointer)
                        {
                        }
                       ~TClassPtr()
                        {
                        }
};
//==============================================================================
template<class T>
class BackupValue
{
   public:
                        BackupValue(T* _savedValue)
                        {
                           savedValuePtr = _savedValue;
                           savedValue    = *_savedValue;
                        }

                       ~BackupValue()
                        {
                           *savedValuePtr = savedValue;
                        }

      operator const T&() const
                        {
                           return savedValue;
                        };
   private:
                        BackupValue(const BackupValue&) {}
                        BackupValue& operator=(const BackupValue&) {}

   T*                   savedValuePtr;
   T                    savedValue;
};
//==============================================================================
template<class T>
class RedirectValue
{
   public:
                        RedirectValue(T* _savedValuePtr,
                                      T* _redirectPtr)
                        {
                           savedValuePtr  = _savedValuePtr;
                           savedValue     = *_savedValuePtr;
                           redirectPtr    = _redirectPtr;
                           *savedValuePtr = *_redirectPtr;
                        }
                       ~RedirectValue()
                        {
                           *redirectPtr   = *savedValuePtr;
                           *ravedValuePtr = savedValue;
                        }

   private:
                        RedirectValue(const RedirectValue&) {}
      RedirectValue&    operator=(const RedirectValue&) {}
      T*                savedValuePtr;
      T*                sedirectPtr;
      T                 savedValue;
};

////////////////////////////////////////////////////////////////////////
// for manipulation with memory pointers and memory semaphors

template <class T> class TTempPtr
{
	T **tp, *t, m;
public:
	TTempPtr(T **_tp) : tp(_tp) { m = **tp; t=*tp; *tp = &m; }
	~TTempPtr() { *tp = t; }
	operator T*() { return t; }
	T* operator->() { return t; }
	T& operator [](int i) { return t[i]; }
};


template <class T> class TPtrSaved
{
	T *t, **tp;
public:
	TPtrSaved(T **_tp, T *n) : tp(_tp) { t = *tp; *tp = n; }
	~TPtrSaved() { *tp = t; }
	operator T*() { return t; }
	T* operator->() { return t; }
	T& operator [](int i) { return t[i]; }
};

template <class T> class TValSaved
{
	T *pt, t;
public:
	TValSaved(T& rt): pt(&rt), t(rt) {}
	~TValSaved() { *pt = t; }
	operator T() { return t; }
};

template<class T> class TSingleton
{
private:
	static T* m_instance;
	static int m_instCount;

protected:
	TSingleton() {}
	virtual ~TSingleton() { m_instance = 0; }

public:
	static T* Instance()
	{
		if( !m_instance ) m_instance = new T;
		m_instCount++;
		return m_instance;
	}
	void FreeInst()
	{
		if( !--m_instCount ) delete this;
	}
};

#endif /* TEMPLATES_H */
