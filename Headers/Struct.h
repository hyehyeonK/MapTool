#pragma once

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;
	D3DXIMAGE_INFO				tImgInfo;

}TEXINFO;


typedef struct tagTile
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vSize;

	BYTE			byOption;
	BYTE			byDrawID;

}TILE;
