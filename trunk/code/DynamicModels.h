#ifndef _DYNAMIC_MODELS_H_
#define _DYNAMIC_MODELS_H_

#include <acknex.h>
#include <d3d9.h>

#define DYNAMIC_FACE_T 1
#define DYNAMIC_QUAD_T 2
#define DYNAMIC_MESH_T 3

typedef struct _D3DXWELDEPSILONS {
  FLOAT Position;
  FLOAT BlendWeights;
  FLOAT Normal;
  FLOAT PSize;
  FLOAT Specular;
  FLOAT Diffuse;
  FLOAT Texcoord[8];
  FLOAT Tangent;
  FLOAT Binormal;
  FLOAT TessFactor;
} D3DXWELDEPSILONS;


#define D3DXWELDEPSILONS_WELDALL				1
#define D3DXWELDEPSILONS_WELDPARTIALMATCHES		2
#define D3DXWELDEPSILONS_DONOTREMOVEVERTICES	4
#define D3DXWELDEPSILONS_DONOTSPLIT				8 

HRESULT WeldVertices(
	LPD3DXMESH pMesh,
	DWORD Flags,
	D3DXWELDEPSILONS *pEpsilons,
	DWORD *pAdjacencyIn,
	DWORD *pAdjacencyOut,
	DWORD *pFaceRemap,
	LPD3DXBUFFER *ppVertexRemap);

typedef void D3DXEFFECTINSTANCE;

#define D3DXF_FILEFORMAT_BINARY		0
#define D3DXF_FILEFORMAT_TEXT		1
#define D3DXF_FILEFORMAT_COMPRESSED	2

HRESULT SaveMeshToX(
	char *pFilename,
	LPD3DXMESH pMesh,
	DWORD *pAdjacency,
	D3DXMATERIAL *pMaterials,
	D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	DWORD Format);

typedef struct
{
	D3DVERTEX v[3];
} DYNAMIC_FACE;

typedef struct
{
	D3DVERTEX v[4];
} DYNAMIC_QUAD;

#define DYNAMIC_MODEL_MAX_VERTEXCOUNT 65536
#define DYNAMIC_MODEL_MAX_INDEXCOUNT 128000

typedef struct
{
	int vertexCount;
	int faceCount;
	D3DVERTEX vertexBuffer[DYNAMIC_MODEL_MAX_VERTEXCOUNT];
	DWORD attributeBuffer[DYNAMIC_MODEL_MAX_VERTEXCOUNT];
	short indexBuffer[DYNAMIC_MODEL_MAX_INDEXCOUNT];
	
	BMAP* skin[4];
} DYNAMIC_MODEL;

#define DYNAMIC_MODELS_FIXNORMALS	(1<<0)
#define DYNAMIC_MODELS_OPTIMIZE		(1<<1)
#define DYNAMIC_MODELS_CLONE_TEX	(1<<2)

typedef struct
{
	int optimization;
	int xFormat;
	long flags;
} DYNAMIC_MODELS_SETTINGS;

///
/// Function pointer to a model action
///
action DynamicModel_TemporaryAction();

///
/// All settings of DynamicModels can be setup in this variable
///
DYNAMIC_MODELS_SETTINGS DynamicModels_Settings;

///
/// Returns 0 if the both vertices aren't equal
///
int DynamicModel_VertexEquals(D3DVERTEX *v1,D3DVERTEX *v2);

///
/// Creates a new dynamic model
///
DYNAMIC_MODEL* DynamicModel_Create();

///
/// Creates a new instance(ENTITY) of the dynamic model
///
ENTITY* DynamicModel_CreateInstance(DYNAMIC_MODEL *model, VECTOR* pos, EVENT act);

///
/// Creates a new DirectX mesh for the dynamic model
///
LPD3DXMESH DynamicModel_CreateMesh(DYNAMIC_MODEL *model);

///
/// Frees the memory allocated by the whole dynamic model
///
void DynamicModel_Delete(DYNAMIC_MODEL *model);

///
/// Adds a new polygon to the dynamic model
///
void DynamicModel_AddFace(DYNAMIC_MODEL *model, DYNAMIC_FACE *face);

///
/// Adds an existing entity to the dynamic model
/// 
void DynamicModel_AddEntity(DYNAMIC_MODEL *model, ENTITY *ent);

///
/// Adds an existing mesh to the dynamic model
///
void DynamicModel_AddMesh(DYNAMIC_MODEL *model, LPD3DXMESH mesh);
void DynamicModel_AddMesh(DYNAMIC_MODEL *model, LPD3DXMESH mesh, VECTOR *offset);
void DynamicModel_AddMesh(DYNAMIC_MODEL *model, LPD3DXMESH mesh, VECTOR *offset, ANGLE *rotation);
void DynamicModel_AddMesh(DYNAMIC_MODEL *model, LPD3DXMESH mesh, VECTOR *offset, ANGLE *rotation, VECTOR *scale);

///
/// Adds a new quad to the dynamic model
///
///		Faces positions
///			0 --- 1
///			|   / |
///			| /   |
///			2 --- 3
///
void DynamicModel_AddQuad(DYNAMIC_MODEL *model, DYNAMIC_QUAD *quad);

///
/// Saves a dynamic model into a DirectX x file
///
void DynamicModel_Save(DYNAMIC_MODEL *model, char *filename);

#include "DynamicModels.c"

#endif