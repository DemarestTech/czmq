/*  =========================================================================
    zsock - high-level socket API that hides libzmq contexts and sockets

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef __ZSOCK_H_INCLUDED__
#define __ZSOCK_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  This interface includes some smart constructors, which create sockets with
//  additional set-up. In all of these, the endpoint is NULL, or starts with
//  '@' (bind) or '>' (connect). Multiple endpoints are allowed, separated by
//  commas. If endpoint does not start with '@' or '>', default action depends
//  on socket type.

//  @warning THE FOLLOWING @INTERFACE BLOCK IS AUTO-GENERATED BY ZPROJECT
//  @warning Please edit the model at "api/zsock.xml" to make changes.
//  @interface
//  This is a stable class, and may not change except for emergencies. It
//  is provided in stable builds.
//  This class has draft methods, which may change over time. They are not
//  in stable releases, by default. Use --enable-drafts to enable.
//  Create a new socket. Returns the new socket, or NULL if the new socket
//  could not be created. Note that the symbol zsock_new (and other       
//  constructors/destructors for zsock) are redirected to the *_checked   
//  variant, enabling intelligent socket leak detection. This can have    
//  performance implications if you use a LOT of sockets. To turn off this
//  redirection behaviour, define ZSOCK_NOCHECK.                          
CZMQ_EXPORT zsock_t *
    zsock_new (int type);

//  Create a PUB socket. Default action is bind.
CZMQ_EXPORT zsock_t *
    zsock_new_pub (const char *endpoint);

//  Create a SUB socket, and optionally subscribe to some prefix string. Default
//  action is connect.                                                          
CZMQ_EXPORT zsock_t *
    zsock_new_sub (const char *endpoint, const char *subscribe);

//  Create a REQ socket. Default action is connect.
CZMQ_EXPORT zsock_t *
    zsock_new_req (const char *endpoint);

//  Create a REP socket. Default action is bind.
CZMQ_EXPORT zsock_t *
    zsock_new_rep (const char *endpoint);

//  Create a DEALER socket. Default action is connect.
CZMQ_EXPORT zsock_t *
    zsock_new_dealer (const char *endpoint);

//  Create a ROUTER socket. Default action is bind.
CZMQ_EXPORT zsock_t *
    zsock_new_router (const char *endpoint);

//  Create a PUSH socket. Default action is connect.
CZMQ_EXPORT zsock_t *
    zsock_new_push (const char *endpoint);

//  Create a PULL socket. Default action is bind.
CZMQ_EXPORT zsock_t *
    zsock_new_pull (const char *endpoint);

//  Create an XPUB socket. Default action is bind.
CZMQ_EXPORT zsock_t *
    zsock_new_xpub (const char *endpoint);

//  Create an XSUB socket. Default action is connect.
CZMQ_EXPORT zsock_t *
    zsock_new_xsub (const char *endpoint);

//  Create a PAIR socket. Default action is connect.
CZMQ_EXPORT zsock_t *
    zsock_new_pair (const char *endpoint);

//  Create a STREAM socket. Default action is connect.
CZMQ_EXPORT zsock_t *
    zsock_new_stream (const char *endpoint);

//  Destroy the socket. You must use this for any socket created via the
//  zsock_new method.                                                   
CZMQ_EXPORT void
    zsock_destroy (zsock_t **self_p);

//  Bind a socket to a formatted endpoint. For tcp:// endpoints, supports   
//  ephemeral ports, if you specify the port number as "*". By default      
//  zsock uses the IANA designated range from C000 (49152) to FFFF (65535). 
//  To override this range, follow the "*" with "[first-last]". Either or   
//  both first and last may be empty. To bind to a random port within the   
//  range, use "!" in place of "*".                                         
//                                                                          
//  Examples:                                                               
//      tcp://127.0.0.1:*           bind to first free port from C000 up    
//      tcp://127.0.0.1:!           bind to random port from C000 to FFFF   
//      tcp://127.0.0.1:*[60000-]   bind to first free port from 60000 up   
//      tcp://127.0.0.1:![-60000]   bind to random port from C000 to 60000  
//      tcp://127.0.0.1:![55000-55999]                                      
//                                  bind to random port from 55000 to 55999 
//                                                                          
//  On success, returns the actual port number used, for tcp:// endpoints,  
//  and 0 for other transports. On failure, returns -1. Note that when using
//  ephemeral ports, a port may be reused by different services without     
//  clients being aware. Protocols that run on ephemeral ports should take  
//  this into account.                                                      
CZMQ_EXPORT int
    zsock_bind (zsock_t *self, const char *format, ...) CHECK_PRINTF (2);

//  Returns last bound endpoint, if any.
CZMQ_EXPORT const char *
    zsock_endpoint (zsock_t *self);

//  Unbind a socket from a formatted endpoint.                     
//  Returns 0 if OK, -1 if the endpoint was invalid or the function
//  isn't supported.                                               
CZMQ_EXPORT int
    zsock_unbind (zsock_t *self, const char *format, ...) CHECK_PRINTF (2);

//  Connect a socket to a formatted endpoint        
//  Returns 0 if OK, -1 if the endpoint was invalid.
CZMQ_EXPORT int
    zsock_connect (zsock_t *self, const char *format, ...) CHECK_PRINTF (2);

//  Disconnect a socket from a formatted endpoint                  
//  Returns 0 if OK, -1 if the endpoint was invalid or the function
//  isn't supported.                                               
CZMQ_EXPORT int
    zsock_disconnect (zsock_t *self, const char *format, ...) CHECK_PRINTF (2);

//  Attach a socket to zero or more endpoints. If endpoints is not null,     
//  parses as list of ZeroMQ endpoints, separated by commas, and prefixed by 
//  '@' (to bind the socket) or '>' (to connect the socket). Returns 0 if all
//  endpoints were valid, or -1 if there was a syntax error. If the endpoint 
//  does not start with '@' or '>', the serverish argument defines whether   
//  it is used to bind (serverish = true) or connect (serverish = false).    
CZMQ_EXPORT int
    zsock_attach (zsock_t *self, const char *endpoints, bool serverish);

//  Returns socket type as printable constant string.
CZMQ_EXPORT const char *
    zsock_type_str (zsock_t *self);

//  Send a 'picture' message to the socket (or actor). The picture is a   
//  string that defines the type of each frame. This makes it easy to send
//  a complex multiframe message in one call. The picture can contain any 
//  of these characters, each corresponding to one or two arguments:      
//                                                                        
//      i = int (signed)                                                  
//      1 = uint8_t                                                       
//      2 = uint16_t                                                      
//      4 = uint32_t                                                      
//      8 = uint64_t                                                      
//      s = char *                                                        
//      b = byte *, size_t (2 arguments)                                  
//      c = zchunk_t *                                                    
//      f = zframe_t *                                                    
//      h = zhashx_t *                                                    
//      U = zuuid_t *                                                     
//      p = void * (sends the pointer value, only meaningful over inproc) 
//      m = zmsg_t * (sends all frames in the zmsg)                       
//      z = sends zero-sized frame (0 arguments)                          
//      u = uint (deprecated)                                             
//                                                                        
//  Note that s, b, c, and f are encoded the same way and the choice is   
//  offered as a convenience to the sender, which may or may not already  
//  have data in a zchunk or zframe. Does not change or take ownership of 
//  any arguments. Returns 0 if successful, -1 if sending failed for any  
//  reason.                                                               
CZMQ_EXPORT int
    zsock_send (void *self, const char *picture, ...);

//  Send a 'picture' message to the socket (or actor). This is a va_list 
//  version of zsock_send (), so please consult its documentation for the
//  details.                                                             
CZMQ_EXPORT int
    zsock_vsend (void *self, const char *picture, va_list argptr);

//  Receive a 'picture' message to the socket (or actor). See zsock_send for
//  the format and meaning of the picture. Returns the picture elements into
//  a series of pointers as provided by the caller:                         
//                                                                          
//      i = int * (stores signed integer)                                   
//      4 = uint32_t * (stores 32-bit unsigned integer)                     
//      8 = uint64_t * (stores 64-bit unsigned integer)                     
//      s = char ** (allocates new string)                                  
//      b = byte **, size_t * (2 arguments) (allocates memory)              
//      c = zchunk_t ** (creates zchunk)                                    
//      f = zframe_t ** (creates zframe)                                    
//      U = zuuid_t * (creates a zuuid with the data)                       
//      h = zhashx_t ** (creates zhashx)                                    
//      p = void ** (stores pointer)                                        
//      m = zmsg_t ** (creates a zmsg with the remaing frames)              
//      z = null, asserts empty frame (0 arguments)                         
//      u = uint * (stores unsigned integer, deprecated)                    
//                                                                          
//  Note that zsock_recv creates the returned objects, and the caller must  
//  destroy them when finished with them. The supplied pointers do not need 
//  to be initialized. Returns 0 if successful, or -1 if it failed to recv  
//  a message, in which case the pointers are not modified. When message    
//  frames are truncated (a short message), sets return values to zero/null.
//  If an argument pointer is NULL, does not store any value (skips it).    
//  An 'n' picture matches an empty frame; if the message does not match,   
//  the method will return -1.                                              
CZMQ_EXPORT int
    zsock_recv (void *self, const char *picture, ...);

//  Receive a 'picture' message from the socket (or actor). This is a    
//  va_list version of zsock_recv (), so please consult its documentation
//  for the details.                                                     
CZMQ_EXPORT int
    zsock_vrecv (void *self, const char *picture, va_list argptr);

//  Send a binary encoded 'picture' message to the socket (or actor). This 
//  method is similar to zsock_send, except the arguments are encoded in a 
//  binary format that is compatible with zproto, and is designed to reduce
//  memory allocations. The pattern argument is a string that defines the  
//  type of each argument. Supports these argument types:                  
//                                                                         
//   pattern    C type                  zproto type:                       
//      1       uint8_t                 type = "number" size = "1"         
//      2       uint16_t                type = "number" size = "2"         
//      4       uint32_t                type = "number" size = "3"         
//      8       uint64_t                type = "number" size = "4"         
//      s       char *, 0-255 chars     type = "string"                    
//      S       char *, 0-2^32-1 chars  type = "longstr"                   
//      c       zchunk_t *              type = "chunk"                     
//      f       zframe_t *              type = "frame"                     
//      u       zuuid_t *               type = "uuid"                      
//      m       zmsg_t *                type = "msg"                       
//      p       void *, sends pointer value, only over inproc              
//                                                                         
//  Does not change or take ownership of any arguments. Returns 0 if       
//  successful, -1 if sending failed for any reason.                       
CZMQ_EXPORT int
    zsock_bsend (void *self, const char *picture, ...);

//  Receive a binary encoded 'picture' message from the socket (or actor).  
//  This method is similar to zsock_recv, except the arguments are encoded  
//  in a binary format that is compatible with zproto, and is designed to   
//  reduce memory allocations. The pattern argument is a string that defines
//  the type of each argument. See zsock_bsend for the supported argument   
//  types. All arguments must be pointers; this call sets them to point to  
//  values held on a per-socket basis.                                      
//  Note that zsock_brecv creates the returned objects, and the caller must 
//  destroy them when finished with them. The supplied pointers do not need 
//  to be initialized. Returns 0 if successful, or -1 if it failed to read  
//  a message.                                                              
CZMQ_EXPORT int
    zsock_brecv (void *self, const char *picture, ...);

//  Set socket to use unbounded pipes (HWM=0); use this in cases when you are
//  totally certain the message volume can fit in memory. This method works  
//  across all versions of ZeroMQ. Takes a polymorphic socket reference.     
CZMQ_EXPORT void
    zsock_set_unbounded (void *self);

//  Send a signal over a socket. A signal is a short message carrying a   
//  success/failure code (by convention, 0 means OK). Signals are encoded 
//  to be distinguishable from "normal" messages. Accepts a zsock_t or a  
//  zactor_t argument, and returns 0 if successful, -1 if the signal could
//  not be sent. Takes a polymorphic socket reference.                    
CZMQ_EXPORT int
    zsock_signal (void *self, byte status);

//  Wait on a signal. Use this to coordinate between threads, over pipe  
//  pairs. Blocks until the signal is received. Returns -1 on error, 0 or
//  greater on success. Accepts a zsock_t or a zactor_t as argument.     
//  Takes a polymorphic socket reference.                                
CZMQ_EXPORT int
    zsock_wait (void *self);

//  If there is a partial message still waiting on the socket, remove and    
//  discard it. This is useful when reading partial messages, to get specific
//  message types.                                                           
CZMQ_EXPORT void
    zsock_flush (void *self);

//  Probe the supplied object, and report if it looks like a zsock_t.
//  Takes a polymorphic socket reference.                            
CZMQ_EXPORT bool
    zsock_is (void *self);

//  Probe the supplied reference. If it looks like a zsock_t instance, return
//  the underlying libzmq socket handle; else if it looks like a file        
//  descriptor, return NULL; else if it looks like a libzmq socket handle,   
//  return the supplied value. Takes a polymorphic socket reference.         
CZMQ_EXPORT void *
    zsock_resolve (void *self);

//  Get socket option `tos`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_tos (void *self);

//  Set socket option `tos`.
CZMQ_EXPORT void
    zsock_set_tos (void *self, int tos);

//  Set socket option `router_handover`.
CZMQ_EXPORT void
    zsock_set_router_handover (void *self, int router_handover);

//  Set socket option `router_mandatory`.
CZMQ_EXPORT void
    zsock_set_router_mandatory (void *self, int router_mandatory);

//  Set socket option `probe_router`.
CZMQ_EXPORT void
    zsock_set_probe_router (void *self, int probe_router);

//  Set socket option `req_relaxed`.
CZMQ_EXPORT void
    zsock_set_req_relaxed (void *self, int req_relaxed);

//  Set socket option `req_correlate`.
CZMQ_EXPORT void
    zsock_set_req_correlate (void *self, int req_correlate);

//  Set socket option `conflate`.
CZMQ_EXPORT void
    zsock_set_conflate (void *self, int conflate);

//  Get socket option `zap_domain`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_zap_domain (void *self);

//  Set socket option `zap_domain`.
CZMQ_EXPORT void
    zsock_set_zap_domain (void *self, const char *zap_domain);

//  Get socket option `mechanism`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_mechanism (void *self);

//  Get socket option `plain_server`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_plain_server (void *self);

//  Set socket option `plain_server`.
CZMQ_EXPORT void
    zsock_set_plain_server (void *self, int plain_server);

//  Get socket option `plain_username`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_plain_username (void *self);

//  Set socket option `plain_username`.
CZMQ_EXPORT void
    zsock_set_plain_username (void *self, const char *plain_username);

//  Get socket option `plain_password`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_plain_password (void *self);

//  Set socket option `plain_password`.
CZMQ_EXPORT void
    zsock_set_plain_password (void *self, const char *plain_password);

//  Get socket option `curve_server`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_curve_server (void *self);

//  Set socket option `curve_server`.
CZMQ_EXPORT void
    zsock_set_curve_server (void *self, int curve_server);

//  Get socket option `curve_publickey`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_curve_publickey (void *self);

//  Set socket option `curve_publickey`.
CZMQ_EXPORT void
    zsock_set_curve_publickey (void *self, const char *curve_publickey);

//  Set socket option `curve_publickey` from 32-octet binary
CZMQ_EXPORT void
    zsock_set_curve_publickey_bin (void *self, const byte *curve_publickey);

//  Get socket option `curve_secretkey`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_curve_secretkey (void *self);

//  Set socket option `curve_secretkey`.
CZMQ_EXPORT void
    zsock_set_curve_secretkey (void *self, const char *curve_secretkey);

//  Set socket option `curve_secretkey` from 32-octet binary
CZMQ_EXPORT void
    zsock_set_curve_secretkey_bin (void *self, const byte *curve_secretkey);

//  Get socket option `curve_serverkey`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_curve_serverkey (void *self);

//  Set socket option `curve_serverkey`.
CZMQ_EXPORT void
    zsock_set_curve_serverkey (void *self, const char *curve_serverkey);

//  Set socket option `curve_serverkey` from 32-octet binary
CZMQ_EXPORT void
    zsock_set_curve_serverkey_bin (void *self, const byte *curve_serverkey);

//  Get socket option `gssapi_server`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_gssapi_server (void *self);

//  Set socket option `gssapi_server`.
CZMQ_EXPORT void
    zsock_set_gssapi_server (void *self, int gssapi_server);

//  Get socket option `gssapi_plaintext`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_gssapi_plaintext (void *self);

//  Set socket option `gssapi_plaintext`.
CZMQ_EXPORT void
    zsock_set_gssapi_plaintext (void *self, int gssapi_plaintext);

//  Get socket option `gssapi_principal`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_gssapi_principal (void *self);

//  Set socket option `gssapi_principal`.
CZMQ_EXPORT void
    zsock_set_gssapi_principal (void *self, const char *gssapi_principal);

//  Get socket option `gssapi_service_principal`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_gssapi_service_principal (void *self);

//  Set socket option `gssapi_service_principal`.
CZMQ_EXPORT void
    zsock_set_gssapi_service_principal (void *self, const char *gssapi_service_principal);

//  Get socket option `ipv6`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_ipv6 (void *self);

//  Set socket option `ipv6`.
CZMQ_EXPORT void
    zsock_set_ipv6 (void *self, int ipv6);

//  Get socket option `immediate`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_immediate (void *self);

//  Set socket option `immediate`.
CZMQ_EXPORT void
    zsock_set_immediate (void *self, int immediate);

//  Set socket option `router_raw`.
CZMQ_EXPORT void
    zsock_set_router_raw (void *self, int router_raw);

//  Get socket option `ipv4only`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_ipv4only (void *self);

//  Set socket option `ipv4only`.
CZMQ_EXPORT void
    zsock_set_ipv4only (void *self, int ipv4only);

//  Set socket option `delay_attach_on_connect`.
CZMQ_EXPORT void
    zsock_set_delay_attach_on_connect (void *self, int delay_attach_on_connect);

//  Get socket option `type`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_type (void *self);

//  Get socket option `sndhwm`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_sndhwm (void *self);

//  Set socket option `sndhwm`.
CZMQ_EXPORT void
    zsock_set_sndhwm (void *self, int sndhwm);

//  Get socket option `rcvhwm`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_rcvhwm (void *self);

//  Set socket option `rcvhwm`.
CZMQ_EXPORT void
    zsock_set_rcvhwm (void *self, int rcvhwm);

//  Get socket option `affinity`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_affinity (void *self);

//  Set socket option `affinity`.
CZMQ_EXPORT void
    zsock_set_affinity (void *self, int affinity);

//  Set socket option `subscribe`.
CZMQ_EXPORT void
    zsock_set_subscribe (void *self, const char *subscribe);

//  Set socket option `unsubscribe`.
CZMQ_EXPORT void
    zsock_set_unsubscribe (void *self, const char *unsubscribe);

//  Get socket option `identity`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_identity (void *self);

//  Set socket option `identity`.
CZMQ_EXPORT void
    zsock_set_identity (void *self, const char *identity);

//  Get socket option `rate`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_rate (void *self);

//  Set socket option `rate`.
CZMQ_EXPORT void
    zsock_set_rate (void *self, int rate);

//  Get socket option `recovery_ivl`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_recovery_ivl (void *self);

//  Set socket option `recovery_ivl`.
CZMQ_EXPORT void
    zsock_set_recovery_ivl (void *self, int recovery_ivl);

//  Get socket option `sndbuf`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_sndbuf (void *self);

//  Set socket option `sndbuf`.
CZMQ_EXPORT void
    zsock_set_sndbuf (void *self, int sndbuf);

//  Get socket option `rcvbuf`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_rcvbuf (void *self);

//  Set socket option `rcvbuf`.
CZMQ_EXPORT void
    zsock_set_rcvbuf (void *self, int rcvbuf);

//  Get socket option `linger`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_linger (void *self);

//  Set socket option `linger`.
CZMQ_EXPORT void
    zsock_set_linger (void *self, int linger);

//  Get socket option `reconnect_ivl`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_reconnect_ivl (void *self);

//  Set socket option `reconnect_ivl`.
CZMQ_EXPORT void
    zsock_set_reconnect_ivl (void *self, int reconnect_ivl);

//  Get socket option `reconnect_ivl_max`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_reconnect_ivl_max (void *self);

//  Set socket option `reconnect_ivl_max`.
CZMQ_EXPORT void
    zsock_set_reconnect_ivl_max (void *self, int reconnect_ivl_max);

//  Get socket option `backlog`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_backlog (void *self);

//  Set socket option `backlog`.
CZMQ_EXPORT void
    zsock_set_backlog (void *self, int backlog);

//  Get socket option `maxmsgsize`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_maxmsgsize (void *self);

//  Set socket option `maxmsgsize`.
CZMQ_EXPORT void
    zsock_set_maxmsgsize (void *self, int maxmsgsize);

//  Get socket option `multicast_hops`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_multicast_hops (void *self);

//  Set socket option `multicast_hops`.
CZMQ_EXPORT void
    zsock_set_multicast_hops (void *self, int multicast_hops);

//  Get socket option `rcvtimeo`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_rcvtimeo (void *self);

//  Set socket option `rcvtimeo`.
CZMQ_EXPORT void
    zsock_set_rcvtimeo (void *self, int rcvtimeo);

//  Get socket option `sndtimeo`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_sndtimeo (void *self);

//  Set socket option `sndtimeo`.
CZMQ_EXPORT void
    zsock_set_sndtimeo (void *self, int sndtimeo);

//  Set socket option `xpub_verbose`.
CZMQ_EXPORT void
    zsock_set_xpub_verbose (void *self, int xpub_verbose);

//  Get socket option `tcp_keepalive`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_tcp_keepalive (void *self);

//  Set socket option `tcp_keepalive`.
CZMQ_EXPORT void
    zsock_set_tcp_keepalive (void *self, int tcp_keepalive);

//  Get socket option `tcp_keepalive_idle`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_tcp_keepalive_idle (void *self);

//  Set socket option `tcp_keepalive_idle`.
CZMQ_EXPORT void
    zsock_set_tcp_keepalive_idle (void *self, int tcp_keepalive_idle);

//  Get socket option `tcp_keepalive_cnt`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_tcp_keepalive_cnt (void *self);

//  Set socket option `tcp_keepalive_cnt`.
CZMQ_EXPORT void
    zsock_set_tcp_keepalive_cnt (void *self, int tcp_keepalive_cnt);

//  Get socket option `tcp_keepalive_intvl`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_tcp_keepalive_intvl (void *self);

//  Set socket option `tcp_keepalive_intvl`.
CZMQ_EXPORT void
    zsock_set_tcp_keepalive_intvl (void *self, int tcp_keepalive_intvl);

//  Get socket option `tcp_accept_filter`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_tcp_accept_filter (void *self);

//  Set socket option `tcp_accept_filter`.
CZMQ_EXPORT void
    zsock_set_tcp_accept_filter (void *self, const char *tcp_accept_filter);

//  Get socket option `rcvmore`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_rcvmore (void *self);

//  Get socket option `fd`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT SOCKET
    zsock_fd (void *self);

//  Get socket option `events`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_events (void *self);

//  Get socket option `last_endpoint`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT char *
    zsock_last_endpoint (void *self);

//  Self test of this class.
CZMQ_EXPORT void
    zsock_test (bool verbose);

#ifdef CZMQ_BUILD_DRAFT_API
//  *** Draft method, for development use, may change without warning ***
//  Create a SERVER socket. Default action is bind.
CZMQ_EXPORT zsock_t *
    zsock_new_server (const char *endpoint);

//  *** Draft method, for development use, may change without warning ***
//  Create a CLIENT socket. Default action is connect.
CZMQ_EXPORT zsock_t *
    zsock_new_client (const char *endpoint);

//  *** Draft method, for development use, may change without warning ***
//  Return socket routing ID if any. This returns 0 if the socket is not
//  of type ZMQ_SERVER or if no request was already received on it.     
CZMQ_EXPORT uint32_t
    zsock_routing_id (zsock_t *self);

//  *** Draft method, for development use, may change without warning ***
//  Set routing ID on socket. The socket MUST be of type ZMQ_SERVER.        
//  This will be used when sending messages on the socket via the zsock API.
CZMQ_EXPORT void
    zsock_set_routing_id (zsock_t *self, uint32_t routing_id);

//  *** Draft method, for development use, may change without warning ***
//  Get socket option `heartbeat_ivl`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_heartbeat_ivl (void *self);

//  *** Draft method, for development use, may change without warning ***
//  Set socket option `heartbeat_ivl`.
CZMQ_EXPORT void
    zsock_set_heartbeat_ivl (void *self, int heartbeat_ivl);

//  *** Draft method, for development use, may change without warning ***
//  Get socket option `heartbeat_ttl`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_heartbeat_ttl (void *self);

//  *** Draft method, for development use, may change without warning ***
//  Set socket option `heartbeat_ttl`.
CZMQ_EXPORT void
    zsock_set_heartbeat_ttl (void *self, int heartbeat_ttl);

//  *** Draft method, for development use, may change without warning ***
//  Get socket option `heartbeat_timeout`.
//  Caller owns return value and must destroy it when done.
CZMQ_EXPORT int
    zsock_heartbeat_timeout (void *self);

//  *** Draft method, for development use, may change without warning ***
//  Set socket option `heartbeat_timeout`.
CZMQ_EXPORT void
    zsock_set_heartbeat_timeout (void *self, int heartbeat_timeout);

#endif // CZMQ_BUILD_DRAFT_API
//  @end

// zsock leak detection - not a part of the official interface to zsock. This
// enables CZMQ to report socket leaks intelligently.
#if defined ZSOCK_NOCHECK
    // no checking active - use the above interface methods directly.
#else
#   define zsock_new(t) zsock_new_checked((t), __FILE__, __LINE__)
#   define zsock_new_pub(e) zsock_new_pub_checked((e), __FILE__, __LINE__)
#   define zsock_new_sub(e,s) zsock_new_sub_checked((e), (s), __FILE__, __LINE__)
#   define zsock_new_req(e) zsock_new_req_checked((e), __FILE__, __LINE__)
#   define zsock_new_rep(e) zsock_new_rep_checked((e), __FILE__, __LINE__)
#   define zsock_new_dealer(e) zsock_new_dealer_checked((e), __FILE__, __LINE__)
#   define zsock_new_router(e) zsock_new_router_checked((e), __FILE__, __LINE__)
#   define zsock_new_pull(e) zsock_new_pull_checked((e), __FILE__, __LINE__)
#   define zsock_new_push(e) zsock_new_push_checked((e), __FILE__, __LINE__)
#   define zsock_new_xpub(e) zsock_new_xpub_checked((e), __FILE__, __LINE__)
#   define zsock_new_xsub(e) zsock_new_xsub_checked((e), __FILE__, __LINE__)
#   define zsock_new_pair(e) zsock_new_pair_checked((e), __FILE__, __LINE__)
#   define zsock_new_stream(e) zsock_new_stream_checked((e), __FILE__, __LINE__)
#   define zsock_destroy(t) zsock_destroy_checked((t), __FILE__, __LINE__)
#endif

CZMQ_EXPORT zsock_t *
    zsock_new_checked (int type, const char *filename, size_t line_nbr);

CZMQ_EXPORT void
    zsock_destroy_checked (zsock_t **self_p, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_pub_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_sub_checked (const char *endpoint, const char *subscribe, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_req_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_rep_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_dealer_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_router_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_push_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_pull_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_xpub_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_xsub_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_pair_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_stream_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_server_checked (const char *endpoint, const char *filename, size_t line_nbr);

CZMQ_EXPORT zsock_t *
    zsock_new_client_checked (const char *endpoint, const char *filename, size_t line_nbr);

#ifdef __cplusplus
}
#endif

#endif
