/*
   (C) 2001 by Argonne National Laboratory.
       See COPYRIGHT in top-level directory.
*/

#define MPE_DIST_GRAPH_CREATE_ADJACENT_ID 215
#define MPE_DIST_GRAPH_CREATE_ID 216
#define MPE_DIST_GRAPH_NEIGHBORS_COUNT_ID 215
#define MPE_DIST_GRAPH_NEIGHBORS_ID 218

void MPE_Init_mpi_distgraph( void )
{
  MPE_State *state;

  state = &states[MPE_DIST_GRAPH_CREATE_ADJACENT_ID];
  state->kind_mask = MPE_KIND_TOPO;
  state->name = "MPI_Dist_graph_create_adjacent";
  state->color="DarkOliveGreen3";
  state->format = NULL;

  state = &states[MPE_DIST_GRAPH_CREATE_ID];
  state->kind_mask = MPE_KIND_TOPO;
  state->name = "MPI_Dist_graph_create";
  state->color="DarkOliveGreen3";
  state->format = NULL;

  state = &states[MPE_DIST_GRAPH_NEIGHBORS_COUNT_ID];
  state->kind_mask = MPE_KIND_TOPO;
  state->name = "MPI_Dist_graph_neighbors_count";
  state->color = "white";
  state->format = NULL;

  state = &states[MPE_DIST_GRAPH_NEIGHBORS_ID];
  state->kind_mask = MPE_KIND_TOPO;
  state->name = "MPI_Dist_graph_neighbors";
  state->color = "white";
  state->format = NULL;
}

int MPI_Dist_graph_create_adjacent( MPI_Comm comm, int indegree, MPE_CONST int sources[],
                                    MPE_CONST int sourceweights[], int outdegree,
                                    MPE_CONST int destinations[], MPE_CONST int destweights[],
                                    MPI_Info info, int reorder, MPI_Comm *out_comm )
{
  int   returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_COMM_DECL
  MPE_LOG_THREADSTM_DECL

/*
    MPI_Dist_graph_create_adjacent - prototyping replacement for MPI_Dist_graph_create_adjacent
    Log the beginning and ending of the time spent in MPI_Dist_graph_create_adjacent calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_DIST_GRAPH_CREATE_ADJACENT_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

    returnVal = PMPI_Dist_graph_create_adjacent( comm, indegree, sources, sourceweights,
                                                 outdegree, destinations, destweights,
                                                 info, reorder, out_comm );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_INTRACOMM(comm,*out_comm,CLOG_COMM_INTRA_CREATE)
  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

  return returnVal;
}

int MPI_Dist_graph_create( MPI_Comm comm,
                           int n, MPE_CONST int sources[], MPE_CONST int degrees[],
                           MPE_CONST int destinations[], MPE_CONST int weights[],
                           MPI_Info info, int reorder, MPI_Comm *out_comm )
{
  int   returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_COMM_DECL
  MPE_LOG_THREADSTM_DECL

/*
    MPI_Dist_graph_create - prototyping replacement for MPI_Dist_graph_create
    Log the beginning and ending of the time spent in MPI_Dist_graph_create calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_DIST_GRAPH_CREATE_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

    returnVal = PMPI_Dist_graph_create( comm,
                                        n, sources, degrees,
                                        destinations, weights,
                                        info, reorder, out_comm );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_INTRACOMM(comm,*out_comm,CLOG_COMM_INTRA_CREATE)
  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

  return returnVal;
}

int MPI_Dist_graph_neighbors_count (MPI_Comm comm, int *indegree, int *outdegree, int *weighted )
{
  int   returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_THREADSTM_DECL

/*
    MPI_Dist_graph_neighbors_count - prototyping replacement for MPI_Dist_graph_neighbors_count
    Log the beginning and ending of the time spent in MPI_Dist_graph_neighbors_count calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_DIST_GRAPH_NEIGHBORS_COUNT_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

  returnVal = PMPI_Dist_graph_neighbors_count( comm, indegree, outdegree, weighted );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

  return returnVal;
}

int MPI_Dist_graph_neighbors( MPI_Comm comm,
                              int maxindegree, int sources[], int sourceweights[],
                              int maxoutdegree, int destinations[], int destweights[] )
{
  int   returnVal;
  MPE_LOG_STATE_DECL
  MPE_LOG_THREADSTM_DECL

/*
    MPI_Dist_graph_neighbors - prototyping replacement for MPI_Dist_graph_neighbors
    Log the beginning and ending of the time spent in MPI_Dist_graph_neighbors calls.
*/

  MPE_LOG_THREADSTM_GET
  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_BEGIN(comm,MPE_DIST_GRAPH_NEIGHBORS_ID)
  MPE_LOG_THREAD_UNLOCK

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_OFF
#endif

  returnVal = PMPI_Dist_graph_neighbors( comm,
                                         maxindegree, sources, sourceweights,
                                         maxoutdegree, destinations, destweights );

#if defined( MAKE_SAFE_PMPI_CALL )
    MPE_LOG_ON
#endif

  MPE_LOG_THREAD_LOCK
  MPE_LOG_STATE_END(comm,NULL)
  MPE_LOG_THREAD_UNLOCK

  return returnVal;
}
