/*
   (C) 2001 by Argonne National Laboratory.
       See COPYRIGHT in top-level directory.
*/

#define MPE_REQ_ADD_COMM(request,comm,comm_out) \
      MPE_Req_add_comm( request, comm, comm_out, commIDs );

void MPE_Req_add_comm( request, comm, comm_out, commIDs)
      MPI_Request     request;
      MPI_Comm        comm;
      MPI_Comm       *comm_out;
const CLOG_CommIDs_t *commIDs;
{
    request_list *newrq;
    rq_alloc( requests_avail_0, newrq );
    if (newrq) {
        newrq->request       = request;
        newrq->commIDs       = commIDs;
        newrq->status        = RQ_COMM;
        newrq->next          = 0;
        newrq->is_persistent = 0;
        rq_add( requests_head_0, requests_tail_0, newrq );
    }
}

#define MPE_COMM_CREATE_GROUP_ID  223
#define MPE_COMM_SPLIT_TYPE_ID 224
#define MPE_COMM_IDUP_ID 225
#define MPE_COMM_DUP_WITH_INFO_ID 226
#define MPE_COMM_SET_INFO_ID 227
#define MPE_COMM_GET_INFO_ID 228

void MPE_Init_mpi_comm30( void )
{
    MPE_State *state;

    state = &states[MPE_COMM_CREATE_GROUP_ID];
    state->kind_mask = MPE_KIND_COMM;
    state->name = "MPI_Comm_create_group";
    state->color = "DarkOliveGreen1";
    state->format = NULL;

    state = &states[MPE_COMM_SPLIT_ID];
    state->kind_mask = MPE_KIND_COMM;
    state->name = "MPI_Comm_split_type";
    state->color = "DarkOliveGreen2";
    state->format = NULL;

    state = &states[MPE_COMM_IDUP_ID];
    state->kind_mask = MPE_KIND_COMM;
    state->name = "MPI_Comm_dup_with_info";
    state->color = "OliveDrab1";
    state->format = NULL;

    state = &states[MPE_COMM_IDUP_ID];
    state->kind_mask = MPE_KIND_COMM;
    state->name = "MPI_Comm_idup";
    state->color = "OliveDrab1";
    state->format = NULL;

    state = &states[MPE_COMM_DUP_WITH_INFO_ID];
    state->kind_mask = MPE_KIND_COMM;
    state->name = "MPI_Comm_dup_with_info";
    state->color = "OliveDrab1";
    state->format = NULL;

    state = &states[MPE_COMM_SET_INFO_ID];
    state->kind_mask = MPE_KIND_COMM;
    state->name = "MPI_Comm_set_info";
    state->color = "purple";
    state->format = NULL;

    state = &states[MPE_COMM_GET_INFO_ID];
    state->kind_mask = MPE_KIND_COMM;
    state->name = "MPI_Comm_get_info";
    state->color = "purple";
    state->format = NULL;
}

int MPI_Comm_create_group( MPI_Comm comm, MPI_Group group, int tag, MPI_Comm *comm_out )
{
  int   returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_COMM_DECL
  MPE_LOG_THREADSTM_DECL

/*
    MPI_Comm_create_group - prototyping replacement for MPI_Comm_create_group
    Log the beginning and ending of the time spent in MPI_Comm_create_group calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_COMM_CREATE_GROUP_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

  returnVal = PMPI_Comm_create_group( comm, group, tag, comm_out );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_COMMCREATE(comm,*comm_out)

  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

  return returnVal;
}

int MPI_Comm_split_type( MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm *comm_out )
{
  int   returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_COMM_DECL
  MPE_LOG_THREADSTM_DECL

/*
    MPI_Comm_split_type - prototyping replacement for MPI_Comm_split_type
    Log the beginning and ending of the time spent in MPI_Comm_split_type calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_COMM_SPLIT_TYPE_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

  returnVal = PMPI_Comm_split_type( comm, split_type, key, info, comm_out );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_COMMCREATE(comm,*comm_out)

  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

  return returnVal;
}

/* Assume we can manipulate attribues in comm_out before waiting the
   request to complete. Anyway, I believe this simple-minded wrapper
   is totally broken, MPE_LOG_COMMCREATE should be used after waiting
   for the request */
int MPI_Comm_idup( MPI_Comm comm, MPI_Comm *comm_out, MPI_Request *request)
{
  int   returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_COMM_DECL
  MPE_LOG_THREADSTM_DECL

/*
    MPI_Comm_dup_with_info - prototyping replacement for MPI_Comm_dup_with_info
    Log the beginning and ending of the time spent in MPI_Comm_dup_with_info calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_COMM_IDUP_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
   MPE_LOG_OFF
#endif

  returnVal = PMPI_Comm_idup( comm, comm_out, request);

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  if (returnVal == MPI_SUCCESS) {
    MPE_LOG_COMMCREATE(comm,*comm_out)
    MPE_REQ_ADD_COMM( *request, comm, comm_out )
  }

  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

  return returnVal;
}

int MPI_Comm_dup_with_info( MPI_Comm comm, MPI_Info info, MPI_Comm *comm_out )
{
  int   returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_COMM_DECL
  MPE_LOG_THREADSTM_DECL

/*
    MPI_Comm_dup_with_info - prototyping replacement for MPI_Comm_dup_with_info
    Log the beginning and ending of the time spent in MPI_Comm_dup_with_info calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_COMM_DUP_WITH_INFO_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
   MPE_LOG_OFF
#endif

  returnVal = PMPI_Comm_dup_with_info( comm, info, comm_out );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_COMMCREATE(comm,*comm_out)

  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

  return returnVal;
}

int MPI_Comm_set_info( MPI_Comm comm, MPI_Info info )
{
    int   returnVal;
    MPE_LOG_STATE_DECL
    MPE_LOG_THREADSTM_DECL

    MPE_LOG_THREADSTM_GET
    MPE_LOG_THREAD_LOCK
    MPE_LOG_STATE_BEGIN(comm,MPE_COMM_SET_INFO_ID)
    MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

    returnVal = PMPI_Comm_set_info( comm, info );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

    MPE_LOG_THREAD_LOCK
    MPE_LOG_STATE_END(comm,NULL)
    MPE_LOG_THREAD_UNLOCK

    return returnVal;
}

int MPI_Comm_get_info( MPI_Comm comm, MPI_Info *info )
{
    int   returnVal;
    MPE_LOG_STATE_DECL
    MPE_LOG_THREADSTM_DECL

    MPE_LOG_THREADSTM_GET
    MPE_LOG_THREAD_LOCK
    MPE_LOG_STATE_BEGIN(comm,MPE_COMM_GET_INFO_ID)
    MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

    returnVal = PMPI_Comm_get_info( comm, info );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

    MPE_LOG_THREAD_LOCK
    MPE_LOG_STATE_END(comm,NULL)
    MPE_LOG_THREAD_UNLOCK

    return returnVal;
}
