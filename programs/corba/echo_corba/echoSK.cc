// This file is generated by omniidl (C++ backend)- omniORB_3_0. Do not edit.

#include "echo.hh"
#include <omniORB3/callDescriptor.h>

static const char* _0RL_library_version = omniORB_3_0;

size_t
Echo::Line::_NP_alignedSize(size_t _initialoffset) const
{
  CORBA::ULong _msgsize = _initialoffset;
  _msgsize += 20;

  return _msgsize;
}

void
Echo::Line::operator>>= (NetBufferedStream &_n) const
{
  _n.put_char_array((const _CORBA_Char*) ((const CORBA::Char*) data), 20);
  
}

void
Echo::Line::operator<<= (NetBufferedStream &_n)
{
  _n.get_char_array((_CORBA_Char*) ((CORBA::Char*) data), 20);
  
}

void
Echo::Line::operator>>= (MemBufferedStream &_n) const
{
  _n.put_char_array((const _CORBA_Char*) ((const CORBA::Char*) data), 20);
  
}

void
Echo::Line::operator<<= (MemBufferedStream &_n)
{
  _n.get_char_array((_CORBA_Char*) ((CORBA::Char*) data), 20);
  
}

Echo_ptr Echo_Helper::_nil() {
  return Echo::_nil();
}

CORBA::Boolean Echo_Helper::is_nil(Echo_ptr p) {
  return CORBA::is_nil(p);

}

void Echo_Helper::release(Echo_ptr p) {
  CORBA::release(p);
}

void Echo_Helper::duplicate(Echo_ptr p) {
  if( p && !p->_NP_is_nil() )  omni::duplicateObjRef(p);
}

size_t Echo_Helper::NP_alignedSize(Echo_ptr obj, size_t offset) {
  return Echo::_alignedSize(obj, offset);
}

void Echo_Helper::marshalObjRef(Echo_ptr obj, NetBufferedStream& s) {
  Echo::_marshalObjRef(obj, s);
}

Echo_ptr Echo_Helper::unmarshalObjRef(NetBufferedStream& s) {
  return Echo::_unmarshalObjRef(s);
}

void Echo_Helper::marshalObjRef(Echo_ptr obj, MemBufferedStream& s) {
  Echo::_marshalObjRef(obj, s);
}

Echo_ptr Echo_Helper::unmarshalObjRef(MemBufferedStream& s) {
  return Echo::_unmarshalObjRef(s);
}

Echo_ptr
Echo::_duplicate(Echo_ptr obj)
{
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);

  return obj;
}

Echo_ptr
Echo::_narrow(CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}

Echo_ptr
Echo::_nil()
{
  static _objref_Echo* _the_nil_ptr = 0;
  if( !_the_nil_ptr ) {
    omni::nilRefLock().lock();
  if( !_the_nil_ptr )  _the_nil_ptr = new _objref_Echo;
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
}

const char* Echo::_PD_repoId = "IDL:Echo:1.0";

_objref_Echo::~_objref_Echo() {}

_objref_Echo::_objref_Echo(const char* mdri,
   IOP::TaggedProfileList* p, omniIdentity* id, omniLocalIdentity* lid) :
   
   omniObjRef(Echo::_PD_repoId, mdri, p, id, lid)
{
  _PR_setobj(this);
}

void*
_objref_Echo::_ptrToObjRef(const char* id)
{
  if( !strcmp(id, CORBA::Object::_PD_repoId) )
    return (CORBA::Object_ptr) this;
  if( !strcmp(id, Echo::_PD_repoId) )
    return (Echo_ptr) this;
  
  return 0;
}

// Proxy call descriptor class. Mangled signature:
//  _cEcho_mLine_i_cEcho_mLine
class _0RL_cd_01531d3e51c81a80_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_01531d3e51c81a80_00000000(LocalCallFn lcfn, const char* op, size_t oplen, _CORBA_Boolean oneway, const Echo::Line& a_0):
     omniCallDescriptor(lcfn, op, oplen, oneway),
     arg_0(a_0) {}

  virtual CORBA::ULong alignedSize(CORBA::ULong size_in);
  virtual void marshalArguments(GIOP_C&);
  
  virtual void unmarshalReturnedValues(GIOP_C&);
    
  inline Echo::Line result() { return pd_result; }
  const Echo::Line& arg_0;
  Echo::Line pd_result;
};

CORBA::ULong _0RL_cd_01531d3e51c81a80_00000000::alignedSize(CORBA::ULong msgsize)
{
  msgsize = arg_0._NP_alignedSize(msgsize);
  
  return msgsize;
}

void _0RL_cd_01531d3e51c81a80_00000000::marshalArguments(GIOP_C& giop_client)
{
  arg_0 >>= giop_client;
  
}

void _0RL_cd_01531d3e51c81a80_00000000::unmarshalReturnedValues(GIOP_C& giop_client)
{
  
  pd_result <<= giop_client;
  
}

// Local call call-back function.
static void
_0RL_lcfn_01531d3e51c81a80_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_01531d3e51c81a80_00000000* tcd = (_0RL_cd_01531d3e51c81a80_00000000*) cd;
  _impl_Echo* impl = (_impl_Echo*) svnt->_ptrToInterface(Echo::_PD_repoId);
  tcd->pd_result = impl->echoString(tcd->arg_0);
}

Echo::Line _objref_Echo::echoString(const Echo::Line& mesg)
{
  _0RL_cd_01531d3e51c81a80_00000000 _call_desc(_0RL_lcfn_01531d3e51c81a80_10000000, "echoString", 11, 0, mesg);
  
  _invoke(_call_desc);
  return _call_desc.result();
}

_pof_Echo::~_pof_Echo() {}

omniObjRef*
_pof_Echo::newObjRef(const char* mdri, IOP::TaggedProfileList* p,
               omniIdentity* id, omniLocalIdentity* lid)
{
  return new _objref_Echo(mdri, p, id, lid);
}

CORBA::Boolean
_pof_Echo::is_a(const char* id) const
{
  if( !strcmp(id, Echo::_PD_repoId) )
    return 1;
  
  return 0;
}

const _pof_Echo _the_pof_Echo;

_impl_Echo::~_impl_Echo() {}

CORBA::Boolean
_impl_Echo::_dispatch(GIOP_S& giop_s)
{
  if( !strcmp(giop_s.operation(), "echoString") ) {
    
    Echo::Line arg_mesg;
    
    arg_mesg <<= giop_s;
    
    giop_s.RequestReceived();
    Echo::Line result;
    
    result = this->echoString(arg_mesg);
    
    if( giop_s.response_expected() ) {
      size_t msgsize = (size_t) GIOP_S::ReplyHeaderSize();
      msgsize = result._NP_alignedSize(msgsize);
      
      giop_s.InitialiseReply(GIOP::NO_EXCEPTION, (CORBA::ULong) msgsize);
      result >>= giop_s;
      
    }
    giop_s.ReplyCompleted();
    return 1;
  }

  return 0;
}

void*
_impl_Echo::_ptrToInterface(const char* id)
{
  if( !strcmp(id, CORBA::Object::_PD_repoId) )
    return (void*) 1;
  if( !strcmp(id, Echo::_PD_repoId) )
    return (_impl_Echo*) this;
  
  return 0;
}

const char*
_impl_Echo::_mostDerivedRepoId()
{
  return Echo::_PD_repoId;
}

POA_Echo::~POA_Echo() {}

