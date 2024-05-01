#pragma once

/*Tree

	Scene has vector of nodes.

	Node
		Object
			CollisionObject
				Ball
				Cube
				Polygon
			LightSource
			ParticleEmiterObject
				PointEmiter
				AttractionSphere
				...

	
	All assets are in one map, referenced by pointers.
	when asset is marked for deletion, all pointers = NULL, next frame, asset is deleted
	
	Asset
		Texture
			Albedo
			NormalMap
			...
		Material
		ParticleEmmiter --Todo
		Shader --Todo
		PolygonMesh --Todo
*/
/*UI's
ObjName
	Node
		pos
		...
	Object
		texture
		normal map
		...
	

*/
/*Drawing
	ObjectDraw
	{
		Material m;
		m.texture = tex;
		...
		drawmaterial(m);
	}

*/
/*
*/

// single-use object to retrive information for ui, or get all properties with labels
class UI_DataPack
{
public:
	std::string name = "Data_Name";

	std::vector<glm::ivec3*> iSliderdata;
	std::vector<std::string> iSliderdatanames;
	std::vector<glm::vec3*> fSliderdata;
	std::vector<std::string> fSliderdatanames;
	
	std::vector<int*> idata;
	std::vector<std::string> idatanames;
	std::vector<bool*> bdata;
	std::vector<std::string> bdatanames;
	std::vector<float*> fdata;
	std::vector<std::string> fdatanames;
	std::vector<std::string*> textdata;
	std::vector<std::string> textdatanames;
	std::vector<std::string*> NoUitextdata;
	std::vector<std::string> NoUitextdatanames;
	std::vector<glm::vec2*> v2data;
	std::vector<std::string> v2datanames;
	std::vector<glm::vec3*> v3data;
	std::vector<std::string> v3datanames;
	std::vector<glm::vec4*> v4data;
	std::vector<std::string> v4datanames;
	std::vector<glm::vec4*> colordata;
	std::vector<std::string> colordatanames;

	std::vector<std::string*> texturedata;
	std::vector<std::string> texturedatanames;

	std::vector<std::string*> materialdata;
	std::vector<std::string> materialdatanames;

	std::vector<std::string*> shaderdata;
	std::vector<std::string> shaderdatanames;

	std::vector<std::string*> ParticleAssetdata;
	std::vector<std::string> ParticleAssetdatanames;

	std::vector<std::string*> polygonDatadata;
	std::vector<std::string> polygonDatadatanames;

	std::vector<polygonData*> p_polygonDatadata;
	std::vector<std::string> p_polygonDatadatanames;

	std::vector<Shader*> s_ShaderDatadata;
	std::vector<std::string> s_ShaderDatadatanames;

	std::vector<Texture*> t_texturedata;
	std::vector<std::string> t_texturedatanames;

	std::vector<Material*> m_materialdata;
	std::vector<std::string> m_materialdatanames;

};

enum ECSType
{
	ECSASSET = 0,
	ECSNODE = 1,
};

enum NodeType
{
	NODE = 0,
	OBJECT = 1,
	COLLISIONOBJECT = 2,
	CO_BALL = 3,
	CO_CUBE = 4,
	CO_POLYGON = 5,
	LIGHTSOURCEOBJECT = 6,
	PARTICLEOBJECT = 7,

};
enum AssetType
{
	ASSET = 0,
	TEXTUREOBJECT = 1,
	MATERIALOBJECT = 2,
	PARTICLEASSET = 3,

};



class Asset
{
public:
	int framesUntillDeletion = 5;
	std::vector<Asset**> UsedAssets;
	int id =0;
	std::string Name = "Asset";
	int type = AssetType::ASSET;

	bool Delete = false;

	Asset()
	{
		type =AssetType::ASSET;
	}

	UI_DataPack GetUIDataAsset()
	{
		UI_DataPack uidp;
		uidp.name = "Asset";
		
		uidp.idata.push_back(&id);
		uidp.idatanames.push_back("ID");
		
		uidp.textdata.push_back(&Name);
		uidp.textdatanames.push_back("Name");
		
		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() 
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataAsset());
		return data;
	}
	virtual void CustomUIDraw(glm::vec2* Corner, float Xstep,float step) {};
	virtual void Ready() {};
	virtual void Process(float dt) {};
	virtual void DebugProcess(float dt) {};
	virtual void DrawPreview(glm::vec2 ui_position, glm::vec2 size)
	{
		UI_DrawCircle(ui_position,size.x,glm::vec4(1.0f),false,NULL,-100);
	};


	virtual ~Asset() {};
	
};

class TextureObject : public Asset
{
public:

	TextureObject()
	{
		type =AssetType::TEXTUREOBJECT;
	}

	Texture texture;

	UI_DataPack GetUIDataTextureObject()
	{
		UI_DataPack uidp;
		uidp.name = "Texture";
		uidp.t_texturedata.push_back(&texture);
		uidp.t_texturedatanames.push_back("texture");		
		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() 
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataAsset());
		data.push_back(GetUIDataTextureObject());

		return data;
	}


	virtual void Ready() override
	{
		texture.Load();
	};
	virtual void DrawPreview(glm::vec2 ui_position, glm::vec2 size) override
	{
		if(texture.texture !=NULL && glIsTexture(texture.texture))
			UI_DrawTexturedQuad(ui_position,size,texture.texture,0.0f,glm::vec4(1.0f),-100);
	};

	virtual ~TextureObject() override
	{
		texture.Delete();
	}
};

inline std::vector<TextureObject*> AvailableTextures;

class MaterialObject : public Asset
{
public:


	Material mater;
	TextureObject* Texture = NULL;
	TextureObject* NormalMap = NULL;
	std::string TextureName = "No_texture";
	std::string NormalMapName = "No_texture";
	MaterialObject()
	{
		type =AssetType::MATERIALOBJECT;
		UsedAssets.push_back((Asset**)&Texture);
		UsedAssets.push_back((Asset**)&NormalMap);
	}

	UI_DataPack GetUIDataMaterialObject()
	{
		UI_DataPack uidp;
		uidp.name = "Material";
		uidp.texturedata.push_back(&TextureName);
		uidp.texturedatanames.push_back("Texture");		
		uidp.texturedata.push_back(&NormalMapName);
		uidp.texturedatanames.push_back("Normal_Map");		
		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() 
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataAsset());
		data.push_back(GetUIDataMaterialObject());

		return data;
	}
	virtual void Process(float dt) override
	{
		bool texexists = false;
		bool normexists = false;
		for(auto tex : AvailableTextures)
		{
			
			if(tex->Name == TextureName && !texexists && !tex->Delete)
			{
				Texture = tex;
				texexists=true;
			}
			if(tex->Name == NormalMapName && !normexists && !tex->Delete)
			{
				NormalMap = tex;
				normexists=true;
			}
		}
		if(!texexists)
			Texture = NULL;
		if(!normexists)
			NormalMap = NULL;

		if(Texture!=NULL)
			mater.Texture = Texture->texture.texture;
		else
			mater.Texture = NULL;

		if(NormalMap!=NULL)
			mater.NormalMap = NormalMap->texture.texture;
		else
			mater.NormalMap = NULL;
	}

	virtual void DrawPreview(glm::vec2 ui_position, glm::vec2 size) override
	{
		UI_DrawQuadWithMaterial(ui_position,size,mater,0.0f,glm::vec4(1.0f),false,-100);
	};

	virtual void Ready() override
	{};
	virtual ~MaterialObject() override
	{

	}
};

inline std::vector<MaterialObject*> AvailableMaterials;

class ParticleAsset : public Asset
{
public:
	ParticleEmiter pe;
	MaterialObject* Mater = NULL;
	std::string MaterialName = "No_Material";
	ParticleAsset()
	{
		type = AssetType::PARTICLEASSET;
		UsedAssets.push_back((Asset**)&Mater);
	}

	UI_DataPack GetUIDataParticleAsset()
	{
		UI_DataPack uidp;
		uidp.name = "ParticleObject";

		uidp.materialdata.push_back(&MaterialName);
		uidp.materialdatanames.push_back("Material");

		uidp.bdata.push_back(&pe.Additive);
		uidp.bdatanames.push_back("Additive");

		uidp.bdata.push_back(&pe.DrawToNormalMap);
		uidp.bdatanames.push_back("DrawToNormalMap");

		uidp.bdata.push_back(&pe.influenced);
		uidp.bdatanames.push_back("influenced");

		uidp.bdata.push_back(&pe.lighted);
		uidp.bdatanames.push_back("lighted");
		
		uidp.idata.push_back(&pe.Z_Index);
		uidp.idatanames.push_back("Z_Index");


		uidp.fdata.push_back(&pe.VelocityDamper);
		uidp.fdatanames.push_back("VelocityDamper");
		uidp.fdata.push_back(&pe.InitialRotation);
		uidp.fdatanames.push_back("InitialRotation");
		uidp.fdata.push_back(&pe.RotationRandomness);
		uidp.fdatanames.push_back("RotationRandomness");
		uidp.fdata.push_back(&pe.RotationVelocity);
		uidp.fdatanames.push_back("RotationVelocity");
		uidp.fdata.push_back(&pe.RotationAcceleration);
		uidp.fdatanames.push_back("RotationAcceleration");
		uidp.fdata.push_back(&pe.RotationDamper);
		uidp.fdatanames.push_back("RotationDamper");
		uidp.fdata.push_back(&pe.InitialOrbitalVelocity);
		uidp.fdatanames.push_back("InitialOrbitalVelocity");
		uidp.fdata.push_back(&pe.OrbitalVelocityRandomness);
		uidp.fdatanames.push_back("OrbitalVelocityRandomness");
		uidp.fdata.push_back(&pe.lifetime);
		uidp.fdatanames.push_back("lifetime");
		uidp.fdata.push_back(&pe.lifetimeRandomness);
		uidp.fdatanames.push_back("lifetimeRandomness");

		uidp.v2data.push_back(&pe.acceleration);
		uidp.v2datanames.push_back("Acceleration");
		uidp.v2data.push_back(&pe.InitialVelocity);
		uidp.v2datanames.push_back("InitialVelocity");
		uidp.v2data.push_back(&pe.StartSize);
		uidp.v2datanames.push_back("StartSize");
		uidp.v2data.push_back(&pe.EndSize);
		uidp.v2datanames.push_back("EndSize");
		uidp.v4data.push_back(&pe.VelocityRandomness);
		uidp.v4datanames.push_back("VelocityRandomness");

		uidp.colordata.push_back(&pe.StartColor);
		uidp.colordatanames.push_back("StartColor");
		uidp.colordata.push_back(&pe.EndColor);
		uidp.colordatanames.push_back("EndColor");
		
		uidp.NoUitextdata.push_back(&pe.Type);
		uidp.NoUitextdatanames.push_back("ParticleEmiterType");

		return uidp;
	}
	
	virtual std::vector<UI_DataPack> GetUIData() override
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataAsset());
		data.push_back(GetUIDataParticleAsset());
		
		return data;
	}

	virtual void CustomUIDraw(glm::vec2* Corner, float Xstep,float step) 
	{
		int tip = 0;
		if(pe.Type == "QUAD") tip = 0;
		if(pe.Type == "LINE") tip = 1;
		if(pe.Type == "CIRCLE") tip = 2;
		if(pe.Type == "TEXTURED") tip = 3;
		if(pe.Type == "TEXTUREDLINE") tip = 4;

		Corner->y += UI_SliderInt(&tip ,(std::string("DrawingType: ") + pe.Type).c_str(), *Corner + glm::vec2(Xstep,0.0f),0,4).y * -1.0f - step;

		if(tip == 0 )  pe.Type = "QUAD";
		if(tip == 1 )  pe.Type = "LINE";
		if(tip == 2 )  pe.Type = "CIRCLE";
		if(tip == 3 )  pe.Type = "TEXTURED";
		if(tip == 4 )  pe.Type = "TEXTUREDLINE";

	}
	void ObjectUpdateMaterial()
	{
		bool texexists = false;
		for(auto tex : AvailableMaterials)
		{
			
			if(tex->Name == MaterialName && !texexists && !tex->Delete)
			{
				Mater = tex;
				texexists=true;
			}
		}
		if(!texexists)
			Mater = NULL;
	}
	virtual void Process(float dt) 
	{
		ObjectUpdateMaterial();
		if(Mater!=NULL)
			pe.material = Mater->mater;
		else
		{
			pe.material.Texture=NULL;
			pe.material.NormalMap=NULL;
		}
			pe.Process(dt);



		pe.SpheresOfInfluence.clear();
		pe.CubesOfInfluence.clear();
		pe.EmitionPoints.clear();
		pe.EmitionCircles.clear();
		pe.EmitionCubes.clear();
		pe.LightSpheres.clear();
		pe.LightCubes.clear();


	}

	virtual void DrawPreview(glm::vec2 ui_position, glm::vec2 size)
	{
		UI_DrawCircle(ui_position,size.x,glm::vec4(1.0f),false,NULL,-100);
	}


};

inline std::vector<ParticleAsset*> AvailableParticleAssets;

class Node
{

public:
	
	int framesUntillDeletion = 5;
	bool Delete = false;
	// array of pointers to pointers of assets
	std::vector<Asset**> UsedAssets;

	int Z_Index = 0;

	int id = 0;
	int type = NodeType::NODE;
	std::string Name = "Node";
	glm::vec2 position = glm::vec2(0.0f);


	Node()
	{
		type = NodeType::NODE;
	}

	UI_DataPack GetUIDataNode()
	{
		UI_DataPack uidp;
		uidp.name = "Node";
		uidp.textdata.push_back(&Name);
		uidp.textdatanames.push_back("Name");

		uidp.idata.push_back(&id);
		uidp.idatanames.push_back("ID");

		uidp.v2data.push_back(&position);
		uidp.v2datanames.push_back("Position");

		uidp.idata.push_back(&Z_Index);
		uidp.idatanames.push_back("Z_Index");

		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() 
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		return data;
	};
	virtual void CustomUIDraw(glm::vec2* Corner, float Xstep,float step) {};
	virtual void Ready() {};
	virtual void Process(float dt) {};
	virtual void Draw() {};
	virtual void DebugDraw() 
	{
		DrawCircle(position,1.0f,{1.0f,1.0f,1.0f,1.0f});
	};
	virtual bool SelectionCheck(glm::vec2 point) 
	{
		ball b;
		b.r = 1.0f;
		b.position = position;
		return BalltoPointCollisionCheck(b,point);
	};
	virtual void DebugProcess(float dt) {};
};

class Object : public Node
{
public:
	glm::vec2 Scale = glm::vec2(1.0f);
	glm::vec4 Color = glm::vec4(1.0f);
	float rotation = 0.0f;
	bool invertX = false;
	bool invertY = false;
	bool Additive = false;
	MaterialObject* Mater = NULL;
	std::string MaterialName = "No_Material";
	Object()
	{
		type = NodeType::OBJECT;
		UsedAssets.push_back((Asset**)&Mater);
	}
	virtual void Ready() override
	{

	}
	void ObjectUpdateMaterial()
	{
		bool texexists = false;
		for(auto tex : AvailableMaterials)
		{
			
			if(tex->Name == MaterialName && !texexists && !tex->Delete)
			{
				Mater = tex;
				texexists=true;
			}
		}
		if(!texexists)
			Mater = NULL;
	}
	virtual void Process(float dt) override
	{
		ObjectUpdateMaterial();
	}

	UI_DataPack GetUIDataObject()
	{
		UI_DataPack uidp;
		uidp.name = "Object";

		uidp.v2data.push_back(&Scale);
		uidp.v2datanames.push_back("Scale");

		uidp.fdata.push_back(&rotation);
		uidp.fdatanames.push_back("Rotation");
		
		uidp.colordata.push_back(&Color);
		uidp.colordatanames.push_back("Color");
		
		uidp.bdata.push_back(&invertX);
		uidp.bdatanames.push_back("invertX");

		uidp.bdata.push_back(&invertY);
		uidp.bdatanames.push_back("invertY");

		uidp.bdata.push_back(&Additive);
		uidp.bdatanames.push_back("Additive");


		uidp.materialdata.push_back(&MaterialName);
		uidp.materialdatanames.push_back("Material");
		
		

		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() override
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		data.push_back(GetUIDataObject());
		return data;
	};

	virtual void Draw() override
	{
		Material m;
		if(Mater!=NULL)
			m = Mater->mater;
		m.flipX = invertX;
		m.flipY = invertY;
		if(m.Texture == NULL)
			m.Texture = FlatColorTexture;
		if(m.NormalMap == NULL)
			m.NormalMap = NULL;


		DrawQuadWithMaterial(position,Scale,m,rotation,Color,Z_Index,Additive);

	};
	virtual bool SelectionCheck(glm::vec2 point) override
	{
		cube NodeCube;
		NodeCube.position =position;
		NodeCube.width = Scale.x;
		NodeCube.height = Scale.y;
		return PointToQuadCollisionCheck(NodeCube, point);
	};
	virtual void DebugDraw() override
	{
		DrawCube(position,Scale,0.0f,{Color.r,Color.g,Color.b,0.2f});
	};

};

class LightSourceObject : public Object
{
public:
	float volume = 0.0f;
	float depth = 0.0f;
	TextureObject* Texture = NULL;
	std::string TextureName = "No_texture";

	LightSourceObject()
	{
		type = NodeType::LIGHTSOURCEOBJECT;
		UsedAssets.push_back((Asset**)&Texture);
	}

	virtual void Ready() override
	{
	}


	virtual void Process(float dt) override
	{
		bool texexists = false;
		for(auto tex : AvailableTextures)
		{
			
			if(tex->Name == TextureName && !texexists && !tex->Delete)
			{
				Texture = tex;
				texexists=true;
			}
		}
		if(!texexists)
			Texture = NULL;

	}

	UI_DataPack GetUIDataLightSourceObject()
	{
		UI_DataPack uidp;
		uidp.name = "LightSource";

		uidp.fdata.push_back(&volume);
		uidp.fdatanames.push_back("Volume");
		
		uidp.fdata.push_back(&depth);
		uidp.fdatanames.push_back("Depth");
		
		uidp.texturedata.push_back(&TextureName);
		uidp.texturedatanames.push_back("Texture");
		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() override
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		data.push_back(GetUIDataObject());
		data[data.size()-1].materialdata.pop_back(); // Additive option
		data[data.size()-1].materialdatanames.pop_back();
		data[data.size()-1].bdata.pop_back(); // Additive option
		data[data.size()-1].bdatanames.pop_back();
		data.push_back(GetUIDataLightSourceObject());
		return data;
	};
	virtual void Draw() override
	{
		if(Texture != NULL)
			DrawLight(glm::vec3(position,depth),Scale,Color,volume,rotation,Texture->texture.texture);
		else 
			DrawLight(glm::vec3(position,depth),Scale,Color,volume,rotation);
	};
	
	virtual void DebugDraw() override
	{
		DrawCube(position,Scale,rotation,{Color.r,Color.g,Color.b,0.2f});
	};
};

class CollisionObject : public Object
{
public:
	int CollisionLayer = 0;
	int CO_type = NodeType::CO_BALL; 
	float roughness = 0;
	float bounciness = 0;
	CollisionObject()
	{
		type = NodeType::COLLISIONOBJECT;
	}
	virtual void Ready() override
	{
	}


	UI_DataPack GetUIDataCollisionObject()
	{
		UI_DataPack uidp;
		uidp.name = "Collision object";
		uidp.idata.push_back(&CollisionLayer);
		uidp.idatanames.push_back("Collision_layer");

		uidp.fdata.push_back(&roughness);
		uidp.fdatanames.push_back("Roughness");

		uidp.fdata.push_back(&bounciness);
		uidp.fdatanames.push_back("Bounciness");

		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() override
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		data.push_back(GetUIDataObject());
		data.push_back(GetUIDataCollisionObject());
		return data;
	};
};

class CO_Ball : public CollisionObject
{
public:
	ball b;
	CO_Ball()
	{
		type = NodeType::CO_BALL;
		b.r = 1.0f;
	}
	virtual void Ready() override
	{
	}
	virtual void Process(float dt) override
	{
		ObjectUpdateMaterial();
		b.position = position;
	}

	UI_DataPack GetUIDataCO_Ball()
	{
		UI_DataPack uidp;
		uidp.name = "Ball";
		uidp.fdata.push_back(&b.r);
		uidp.fdatanames.push_back("Radius");	

		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() override
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		data.push_back(GetUIDataObject());
		data.push_back(GetUIDataCollisionObject());
		data.push_back(GetUIDataCO_Ball());
		return data;
	};
	
	virtual void Draw() override
	{
		Material m;

		if(Mater !=NULL)
		{
			m = Mater->mater;
		}
		m.flipX = invertX;
		m.flipY = invertY;
		if(m.Texture == NULL)
			m.Texture = FlatColorCircleTexture;
		if(m.NormalMap == NULL)
			m.NormalMap = NULL;

		DrawQuadWithMaterial(position,Scale,m,rotation,Color,Z_Index,Additive);

	};
	virtual void DebugDraw() override
	{
		DrawCircle(position,b.r,{Color.r,Color.g,Color.b,0.2f});
	};
	virtual bool SelectionCheck(glm::vec2 point) override
	{
		return BalltoPointCollisionCheck(b,point);
	};
};

class CO_Cube : public CollisionObject
{
public:
	cube c;

	CO_Cube()
	{
		type = NodeType::CO_CUBE;
		c.width = 1.0f;
		c.height = 1.0f;
	}
	virtual void Ready() override
	{
	}
	virtual void Process(float dt) override
	{
		ObjectUpdateMaterial();
		c.position = position;
	}
	UI_DataPack GetUIDataCO_Cube()
	{
		UI_DataPack uidp;
		uidp.name = "Cube";
		uidp.fdata.push_back(&c.width);
		uidp.fdatanames.push_back("Width");
		uidp.fdata.push_back(&c.height);
		uidp.fdatanames.push_back("Height");	

		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() override
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		data.push_back(GetUIDataObject());
		data.push_back(GetUIDataCollisionObject());
		data.push_back(GetUIDataCO_Cube());
		return data;
	};
	virtual bool SelectionCheck(glm::vec2 point) override
	{
		cube NodeCube;
		NodeCube.position =position;
		NodeCube.width = c.width;
		NodeCube.height = c.height;
		return PointToQuadCollisionCheck(NodeCube, point);
	};
	virtual void DebugDraw() override
	{
		DrawCube(c,{Color.r,Color.g,Color.b,0.2f});		
	};
};

class CO_Polygon : public CollisionObject
{
public:
	polygon p;
	std::string PolygonMeshName = "No_mesh";
	CO_Polygon()
	{
		type = NodeType::CO_POLYGON;
	}
	virtual void Ready() override
	{
	}

	UI_DataPack GetUIDataCO_Polygon()
	{
		UI_DataPack uidp;
		uidp.name = "Polygon";
		uidp.polygonDatadata.push_back(&PolygonMeshName);
		uidp.polygonDatadatanames.push_back("Mesh");	

		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() override
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		data.push_back(GetUIDataObject());
		data.push_back(GetUIDataCollisionObject());
		data.push_back(GetUIDataCO_Polygon());
		return data;
	};
	virtual void Draw() override
	{
		// if(Mater!=NULL)
		// {
		// 	p.Texture = Mater->mater.Texture;
		// 	p.NormalMap = Mater->mater.NormalMap;
		// }
		// p.color = Color;
		// p.Scale = Scale;
		// p.Rotation = rotation;
		// p.Update_Shape();
		// DrawPolygon(&p);
	};
	virtual void DebugDraw() override
	{
		// p.color = Color;
		// p.Scale = Scale;
		// p.Rotation = rotation;
		// p.color.a = 0.2f;
		// p.Texture = NULL;
		// p.NormalMap = NULL;
		// DrawPolygon(&p);
	};
};

class ParticleObject : public Node
{
public:

	glm::ivec3 po_typeData = glm::ivec3(0,0,6); 

	ParticleAsset* partAsset = NULL;
	std::string partAssetName = "None";

	glm::vec2 velocity = glm::vec2(0.0f);
	glm::vec2 scale = glm::vec2(1.0f);
	glm::vec4 Color = glm::vec4(1.0f);
	int amount = 1;
	float tick = 0.017f;
	float r = 1.0f;
	bool attractive = false;
	float attractionStrength = 1.0f;

	float t = 0.0f;

	ParticleEmiter::influenceSphere po_influenceSphere;
	ParticleEmiter::influenceCube po_influenceCube;
	ParticleEmiter::EmitionPoint po_EmitionPoint;
	ParticleEmiter::EmitionCircle po_EmitionCircle;
	ParticleEmiter::EmitionCube po_EmitionCube;
	ParticleEmiter::LightSphere po_LightSphere;
	ParticleEmiter::LightCube po_LightCube;



	ParticleObject()
	{
		type = NodeType::PARTICLEOBJECT;
		UsedAssets.push_back((Asset**)&partAsset);
	}

	UI_DataPack GetUIDataParticleObject()
	{
		UI_DataPack uidp;
		uidp.name = "ParticleEmiterObject";

		uidp.ParticleAssetdata.push_back(&partAssetName);
		uidp.ParticleAssetdatanames.push_back("ParticleAsset");

		uidp.iSliderdata.push_back(&po_typeData);
		uidp.iSliderdatanames.push_back("ParticleObjectType");

		switch (po_typeData.x)
		{
		case 0:
			uidp.v2data.push_back(&velocity);
			uidp.v2datanames.push_back("velocity");
			
			uidp.fdata.push_back(&r);
			uidp.fdatanames.push_back("Radius");
			uidp.fdata.push_back(&attractionStrength);
			uidp.fdatanames.push_back("AttractionStrength");
			uidp.bdata.push_back(&attractive);
			uidp.bdatanames.push_back("Attractive");

			
			break;
		case 1:
			uidp.v2data.push_back(&scale);
			uidp.v2datanames.push_back("scale");
			uidp.v2data.push_back(&velocity);
			uidp.v2datanames.push_back("velocity");
			
			uidp.fdata.push_back(&attractionStrength);
			uidp.fdatanames.push_back("AttractionStrength");
			uidp.bdata.push_back(&attractive);
			uidp.bdatanames.push_back("Attractive");

			break;
		case 2:
			uidp.v2data.push_back(&velocity);
			uidp.v2datanames.push_back("velocity");
			
			uidp.idata.push_back(&amount);
			uidp.idatanames.push_back("amount");
			uidp.fdata.push_back(&tick);
			uidp.fdatanames.push_back("tick");
			break;
		case 3:
			uidp.v2data.push_back(&velocity);
			uidp.v2datanames.push_back("velocity");
			
			uidp.fdata.push_back(&r);
			uidp.fdatanames.push_back("Radius");
			uidp.idata.push_back(&amount);
			uidp.idatanames.push_back("amount");
			uidp.fdata.push_back(&tick);
			uidp.fdatanames.push_back("tick");

			break;
		case 4:
			uidp.v2data.push_back(&scale);
			uidp.v2datanames.push_back("scale");
			uidp.v2data.push_back(&velocity);
			uidp.v2datanames.push_back("velocity");
			
			uidp.idata.push_back(&amount);
			uidp.idatanames.push_back("amount");
			uidp.fdata.push_back(&tick);
			uidp.fdatanames.push_back("tick");
			break;
		case 5:
			uidp.v4data.push_back(&Color);
			uidp.v4datanames.push_back("Color");
			
			uidp.fdata.push_back(&r);
			uidp.fdatanames.push_back("Radius");

			break;
		case 6:
			uidp.v2data.push_back(&scale);
			uidp.v2datanames.push_back("scale");

			uidp.v4data.push_back(&Color);
			uidp.v4datanames.push_back("Color");
			
			break;
		}

		return uidp;
	}
	virtual std::vector<UI_DataPack> GetUIData() 
	{
		std::vector<UI_DataPack> data;
		data.push_back(GetUIDataNode());
		data[data.size()-1].idata.pop_back();//Z_Index
		data[data.size()-1].idatanames.pop_back();
		data.push_back(GetUIDataParticleObject());
		return data;
	}
	virtual void Process(float dt) override
	{
		if (t > tick)
			t = 0.0f;

		t+=dt;
		bool texexists = false;
		for(auto tex : AvailableParticleAssets)
		{
			
			if(tex->Name == partAssetName && !texexists && !tex->Delete)
			{
				partAsset = tex;
				texexists=true;
			}
		}

		if(!texexists)
			partAsset = NULL;

		if(partAsset!=NULL)
		{
			switch (po_typeData.x)
			{
			case 0:
				po_influenceSphere.position=position;
				po_influenceSphere.velocity=velocity;

				po_influenceSphere.r = r;
				po_influenceSphere.attractive = attractive;
				po_influenceSphere.attractionStrength = attractionStrength;
				
				partAsset->pe.SpheresOfInfluence.push_back(po_influenceSphere);
				break;
			case 1:
				po_influenceCube.position = position;
				po_influenceCube.scale = scale;
				po_influenceCube.velocity = velocity;

				po_influenceCube.attractive = attractive;
				po_influenceCube.attractionStrength = attractionStrength;

				partAsset->pe.CubesOfInfluence.push_back(po_influenceCube);
				break;
			case 2:
				po_EmitionPoint.position = position;
				po_EmitionPoint.velocity = velocity;
				po_EmitionPoint.amount = amount;
				po_EmitionPoint.tick = tick;
				po_EmitionPoint.t = t;
				partAsset->pe.EmitionPoints.push_back(po_EmitionPoint);
				break;
			case 3:
				po_EmitionCircle.position = position;
				po_EmitionCircle.velocity = velocity;
				po_EmitionCircle.r = r;
				po_EmitionCircle.amount = amount;
				po_EmitionCircle.tick = tick;
				po_EmitionCircle.t = t;

				partAsset->pe.EmitionCircles.push_back(po_EmitionCircle);
				break;
			case 4:
				po_EmitionCube.position = position;
				po_EmitionCube.scale = scale;
				po_EmitionCube.velocity = velocity;
				po_EmitionCube.t = t;

				po_EmitionCube.amount = amount;	
				po_EmitionCube.tick = tick;
				partAsset->pe.EmitionCubes.push_back(po_EmitionCube);
				break;
			case 5:
				po_LightSphere.r = r;

				po_LightSphere.position = position;
				po_LightSphere.Color = Color;

				partAsset->pe.LightSpheres.push_back(po_LightSphere);
				break;
			case 6:
				po_LightCube.position = position;
				po_LightCube.scale = scale;
				po_LightCube.Color = Color;

				partAsset->pe.LightCubes.push_back(po_LightCube);
				break;
			
			default:
				break;
			}

		}

	}
	virtual bool SelectionCheck(glm::vec2 point) override
	{
		ball b;
		cube NodeCube;
		switch (po_typeData.x)
		{	
		case 0:
			b.r = r;
			b.position = position;
			return BalltoPointCollisionCheck(b,point);
		case 1:
			NodeCube.position =position;
			NodeCube.width = scale.x;
			NodeCube.height = scale.y;
			return PointToQuadCollisionCheck(NodeCube, point);
		case 2:
				
			b.r = 1.0f;
			b.position = position;
			return BalltoPointCollisionCheck(b,point);
		case 3:
			b.r = r;
			b.position = position;
			return BalltoPointCollisionCheck(b,point);
		case 4:
			NodeCube.position =position;
			NodeCube.width = scale.x;
			NodeCube.height = scale.y;
			return PointToQuadCollisionCheck(NodeCube, point);
		case 5:
			b.r = r;
			b.position = position;
			return BalltoPointCollisionCheck(b,point);
		case 6:
			NodeCube.position =position;
			NodeCube.width = scale.x;
			NodeCube.height = scale.y;
			return PointToQuadCollisionCheck(NodeCube, point);
		
		default:
			return false;
		}
	};
	virtual void DebugDraw() 
	{
		switch (po_typeData.x)
		{	
		case 0:
			DrawCircle(position,r,glm::vec4(1.0f,1.0f,2.0f,0.2f));
			break;
		case 1:
			DrawCube(position,scale,0.0f,glm::vec4(1.0f,1.0f,2.0f,0.2f));
			break;
		case 2:
			DrawCircle(position,1.0f,{1.0f,2.0f,1.0f,1.0f});
			break;
		case 3:
			DrawCircle(position,r,glm::vec4(1.0f,2.0f,1.0f,0.2f));
			break;
		case 4:
			DrawCube(position,scale,0.0f,glm::vec4(1.0f,2.0f,1.0f,0.2f));
			break;
		case 5:
			DrawCircle(position,r,glm::vec4(2.0f,2.0f,1.0f,0.2f));
			break;
		case 6:
			DrawCube(position,scale,0.0f,glm::vec4(2.0f,2.0f,1.0f,0.2f));
			break;
		
		default:
			break;
		}
	}
};

inline Node* CreateNewNodeByClassId(int ID)
{
	switch (ID)
	{
	case NodeType::NODE:
		return new Node();
		break;
	case NodeType::OBJECT:
		return new Object();
		break;
	case NodeType::COLLISIONOBJECT:
		return new CollisionObject();
		break;
	case NodeType::CO_BALL:
		return new CO_Ball();
		break;
	case NodeType::CO_CUBE:
		return new CO_Cube();
		break;
	case NodeType::CO_POLYGON:
		return new CO_Polygon();
		break;
	case NodeType::LIGHTSOURCEOBJECT:
		return new LightSourceObject();
		break;
	case NodeType::PARTICLEOBJECT:
		return new ParticleObject();
		break;
	
	default:
		break;
	}
	return NULL;


}
 
inline Asset* CreateNewAssetByClassId(int ID)
{
	switch (ID)
	{
	case AssetType::ASSET:
		return new Asset();
		break;
	case AssetType::TEXTUREOBJECT:
		return new TextureObject();
		break;
	case AssetType::MATERIALOBJECT:
		return new MaterialObject();
		break;
	case AssetType::PARTICLEASSET:
		return new ParticleAsset();
		break;
	
	default:
		break;
	}
	
	
	return NULL;
}

class Scene
{
	bool firstframe = true;
public:
	bool DrawCollisions = true;
	bool DrawRegularScene = true;
	

	std::vector<polygon*> Collision_polygons;
	std::vector<cube*> Collision_cubes;
	std::vector<ball*> Collision_balls;

	std::vector<Node*> Nodes;
	std::vector<Asset*> Assets;


	void SaveAs(std::string filename);
	void LoadFrom(std::string filename);
	void Rescale(glm::vec2 scale, int Z_Index = 0);
	void Draw(float dt = 0.017f);
	void DeleteNormalMaps();
	void DeleteTextures();
	void ReloadTextures();
};
