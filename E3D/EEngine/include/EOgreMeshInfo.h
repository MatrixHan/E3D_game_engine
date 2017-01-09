
#pragma once

namespace E3D
{

	// Ogre Mesh文件相关信息

	// Ogre Mesh二进制文件中的ID枚举, 来源--Ogre
	enum OGREMESHID
	{
		//unsigned short --- uint32
		M_HEADER              = 0x1000,
			// char*          version   : Version number check
		M_MESH                = 0x3000,
			// bool skeletallyAnimated   // important flag which affects h/w buffer policies
			M_SUBMESH             = 0x4000, 
				// char* materialName
				// bool useSharedVertices
				// unsigned int indexCount
				// bool indexes32Bit
				// unsigned int* faceVertexIndices (indexCount)
				// OR
				// unsigned short* faceVertexIndices (indexCount)
				// M_GEOMETRY chunk (Optional: present only if useSharedVertices = false)
				M_GEOMETRY          = 0x5000, // NB this chunk is embedded within M_MESH and M_SUBMESH
					// unsigned int vertexCount
					M_GEOMETRY_VERTEX_DECLARATION = 0x5100,
						M_GEOMETRY_VERTEX_ELEMENT = 0x5110, // Repeating section
							// unsigned short source;  	// buffer bind source
							// unsigned short type;    	// VertexElementType
							// unsigned short semantic; // VertexElementSemantic
							// unsigned short offset;	// start offset in buffer in bytes
							// unsigned short index;	// index of the semantic (for colours and texture coords)
					M_GEOMETRY_VERTEX_BUFFER = 0x5200, // Repeating section
						// unsigned short bindIndex;	// Index to bind this buffer to
						// unsigned short vertexSize;	// Per-vertex size, must agree with declaration at this index
						M_GEOMETRY_VERTEX_BUFFER_DATA = 0x5210,
							// raw buffer data
            				// float* pVertices (x, y, z order x numVertices)
							// float* pNormals (x, y, z order x numVertices)
							// float* pTexCoords  (u v dimensions x numVertices)

				M_SUBMESH_OPERATION = 0x4010, // optional, trilist assumed if missing
					// unsigned short operationType

			M_MESH_BOUNDS = 0x9000,
				// float minx, miny, minz
				// float maxx, maxy, maxz
				// float radius
			
			M_SUBMESH_NAME_TABLE = 0xA000,
				// Subchunks of the name table. Each chunk contains an index & string
				M_SUBMESH_NAME_TABLE_ELEMENT = 0xA100,
					// short index
					// char* name
	};

	/// The rendering operation type to perform
	enum OperationType {
		/// A list of points, 1 vertex per point
		OT_POINT_LIST = 1,
		/// A list of lines, 2 vertices per line
		OT_LINE_LIST = 2,
		/// A strip of connected lines, 1 vertex per line plus 1 start vertex
		OT_LINE_STRIP = 3,
		/// A list of triangles, 3 vertices per triangle
		OT_TRIANGLE_LIST = 4,
		/// A strip of triangles, 3 vertices for the first triangle, and 1 per triangle after that 
		OT_TRIANGLE_STRIP = 5,
		/// A fan of triangles, 3 vertices for the first triangle, and 1 per triangle after that
		OT_TRIANGLE_FAN = 6
	};
}
