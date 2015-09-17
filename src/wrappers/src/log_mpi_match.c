/*
   (C) 2001 by Argonne National Laboratory.
       See COPYRIGHT in top-level directory.
*/
/*
   This file should be INCLUDED into log_mpi_core.c when adding the
   MPI3 matched probe and receive routines to the profiling list

   Also set MPE_MAX_KNOWN_STATES >= 200
*/

#define MPE_REQ_ADD_MATCH(request,datatype,count,source,tag,comm) \
    if (source != MPI_PROC_NULL) { \
       MPE_Req_add_match( request, datatype, count, commIDs ); \
    }

void MPE_Req_add_match( request, datatype, count, commIDs)
      MPI_Request     request;
      MPI_Datatype    datatype;
const CLOG_CommIDs_t *commIDs;
      int             count;
{
    request_list *newrq;

    rq_alloc( requests_avail_0, newrq );
    if (newrq) {
        newrq->request       = request;
        newrq->commIDs       = commIDs;
        newrq->status        = RQ_MATCH;
        newrq->next          = 0;
        newrq->is_persistent = 0;
        rq_add( requests_head_0, requests_tail_0, newrq );
    }
}

#define MPE_MPROBE_ID 219
#define MPE_MRECV_ID 220
#define MPE_IMPROBE_ID 221
#define MPE_IMRECV_ID 222

void MPE_Init_mpi_match( void )
{
  MPE_State *state;

  state = &states[MPE_MPROBE_ID];
  state->kind_mask = MPE_KIND_MSG;
  state->name = "MPI_Mprobe";
  state->color = "lavender";
  state->format = NULL;

  state = &states[MPE_MRECV_ID];
  state->kind_mask = MPE_KIND_MSG;
  state->name = "MPI_Mrecv";
  state->color = "green";
  state->format = NULL;

  state = &states[MPE_IMPROBE_ID];
  state->kind_mask = MPE_KIND_MSG;
  state->name = "MPI_Improbe";
  state->color = "LavenderBlush";
  state->format = NULL;

  state = &states[MPE_IMRECV_ID];
  state->kind_mask = MPE_KIND_MSG;
  state->name = "MPI_Imrecv";
  state->color = "PaleGreen";
  state->format = NULL;

}

int MPI_Mprobe(int source, int tag, MPI_Comm comm,
               MPI_Message *message, MPI_Status *status)
{
  int  returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_THREADSTM_DECL

#ifdef HAVE_MPI_STATUS_IGNORE
  MPI_Status    tmp_status;
  if (status == MPI_STATUS_IGNORE)
      status = &tmp_status;
#endif

/*
    MPI_Mprobe - prototyping replacement for MPI_Mprobe
    Log the beginning and ending of the time spent in MPI_Mprobe calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_MPROBE_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

  returnVal = PMPI_Mprobe( source, tag, comm, message, status );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

#ifdef HAVE_MPI_STATUS_BROKEN_ON_PROC_NULL
  if (status && source == MPI_PROC_NULL) {
      status->MPI_SOURCE = MPI_PROC_NULL;
      status->MPI_TAG    = MPI_ANY_TAG;
#ifdef HAVE_MPI_STATUS_SET_ELEMENTS
      MPI_Status_set_elements( status, MPI_BYTE, 0 );
#endif
  }
#endif

  return returnVal;
}

int MPI_Mrecv(void *buf, int count, MPI_Datatype datatype,
              MPI_Message *message, MPI_Status *status)
{
  int  returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_THREADSTM_DECL
#ifdef HAVE_MPI_STATUS_BROKEN_ON_PROC_NULL
  int source = MPI_ANY_SOURCE;
#endif
#ifdef HAVE_MPI_STATUS_IGNORE
  MPI_Status    tmp_status;
  if (status == MPI_STATUS_IGNORE)
      status = &tmp_status;
#endif

/*
    MPI_Mrecv - prototyping replacement for MPI_Mrecv
    Log the beginning and ending of the time spent in MPI_Mrecv calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(MPE_COMM_NULL,MPE_MRECV_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

#ifdef HAVE_MPI_STATUS_BROKEN_ON_PROC_NULL
  if (message && *message == MPI_MESSAGE_NO_PROC) source = MPI_PROC_NULL;
#endif
  returnVal = PMPI_Mrecv( buf, count, datatype, message, status );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_END(MPE_COMM_NULL,NULL)
  MPE_LOG_THREAD_UNLOCK

#ifdef HAVE_MPI_STATUS_BROKEN_ON_PROC_NULL
  if (status && source == MPI_PROC_NULL) {
      status->MPI_SOURCE = MPI_PROC_NULL;
      status->MPI_TAG    = MPI_ANY_TAG;
#ifdef HAVE_MPI_STATUS_SET_ELEMENTS
      MPI_Status_set_elements( status, datatype, 0 );
#endif
  }
#endif

  return returnVal;
}

int MPI_Improbe(int source, int tag, MPI_Comm comm, int *flag,
                MPI_Message *message, MPI_Status *status)
{
  int  returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_THREADSTM_DECL

#ifdef HAVE_MPI_STATUS_IGNORE
  MPI_Status    tmp_status;
  if (status == MPI_STATUS_IGNORE)
      status = &tmp_status;
#endif

/*
    MPI_Improbe - prototyping replacement for MPI_Improbe
    Log the beginning and ending of the time spent in MPI_Improbe calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_IMPROBE_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

  returnVal = PMPI_Improbe( source, tag, comm, flag, message, status );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

#ifdef HAVE_MPI_STATUS_BROKEN_ON_PROC_NULL
  if (status && source == MPI_PROC_NULL) {
      status->MPI_SOURCE = MPI_PROC_NULL;
      status->MPI_TAG    = MPI_ANY_TAG;
#ifdef HAVE_MPI_STATUS_SET_ELEMENTS
      MPI_Status_set_elements( status, datatype, 0 );
#endif
  }
#endif

  return returnVal;
}

int MPI_Imrecv(void *buf, int count, MPI_Datatype datatype,
               MPI_Message *message, MPI_Request *request)
{
  int  returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_THREADSTM_DECL
  int source = MPI_ANY_SOURCE;

/*
    MPI_Imrecv - prototyping replacement for MPI_Imrecv
    Log the beginning and ending of the time spent in MPI_Imrecv calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(MPE_COMM_NULL,MPE_IMRECV_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

  if (message && *message == MPI_MESSAGE_NO_PROC) source = MPI_PROC_NULL;
  returnVal = PMPI_Imrecv( buf, count, datatype, message, request );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  if (returnVal == MPI_SUCCESS) {
    MPE_REQ_ADD_MATCH( *request, datatype, count, source, MPI_ANY_TAG, MPE_COMM_NULL)
  }

  MPE_LOG_STATE_END(MPE_COMM_NULL,NULL)
  MPE_LOG_THREAD_UNLOCK

  return returnVal;
}
