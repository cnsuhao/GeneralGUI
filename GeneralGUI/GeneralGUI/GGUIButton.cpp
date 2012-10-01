//-----------------------------------------------------------------------------
// GGUI Button控件
// (C) oil
// 2012-09-30
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIButton.h"
#include "GGUITexture.h"
#include "GGUITextureContainer.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUIButton::GGUIButton()
	:m_eButtonState(ButtonState_Normal)
	{
		m_eMyWindowType = WindowType_Button;
	}
	//-----------------------------------------------------------------------------
	GGUIButton::~GGUIButton()
	{

	}
	//-----------------------------------------------------------------------------
	void GGUIButton::SetEnable(bool bEnable)
	{
		//把旧值保存下来。
		bool bOldValue = m_bEnable;
		__super::SetEnable(bEnable);
		//
		if (bOldValue != bEnable)
		{
			eButtonState eDestState = bEnable ? ButtonState_Normal : ButtonState_Disable;
			if (m_eButtonState != eDestState)
			{
				m_eButtonState = eDestState;
				m_bShouldUpdateUITexture = true;
			}
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::UpdateUITexture()
	{
		static SoFloat s_fColorReduce = 1.0f;
		static SoFloat s_fDeltaX = 2.0f;
		static SoFloat s_fDeltaY = 2.0f;

		GGUITexture* pUITexture = GGUITextureContainer::GetInstance()->GetUITexture(m_nMyTextureID);
		if (pUITexture)
		{
			SoFloat fDestColorR = m_fColorR;
			SoFloat fDestColorG = m_fColorG;
			SoFloat fDestColorB = m_fColorB;
			SoFloat fDestPosX = m_fPositionX;
			SoFloat fDestPosY = m_fPositionY;
			switch (m_eButtonState)
			{
			case ButtonState_Normal:
				break;
			case ButtonState_Hover:
				{
					fDestColorR = m_fColorR * s_fColorReduce;
					fDestColorG = m_fColorG * s_fColorReduce;
					fDestPosX = m_fPositionX - s_fDeltaX;
					fDestPosY = m_fPositionY - s_fDeltaY;
				}
				break;
			case ButtonState_PushDown:
				{
					fDestColorG = m_fColorG * s_fColorReduce;
					fDestColorB = m_fColorB * s_fColorReduce;
					fDestPosX = m_fPositionX + s_fDeltaX;
					fDestPosY = m_fPositionY + s_fDeltaY;
				}
				break;
			case ButtonState_Disable:
				{
					fDestColorR = m_fColorR * s_fColorReduce;
					fDestColorG = m_fColorG * s_fColorReduce;
					fDestColorB = m_fColorB * s_fColorReduce;
				}
				break;
			}
			SoUInt32 uiColor = SoMakeColorRGBA(fDestColorR, fDestColorG, fDestColorB, m_fColorA);
			pUITexture->UpdateVertexBuffer(fDestPosX, fDestPosY, m_fPositionZ, m_fWidth, m_fHeight, uiColor);
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseEnterWindowArea()
	{
		__super::OnMouseEnterWindowArea();
		if (m_bEnable)
		{
			if (m_eButtonState != ButtonState_Hover)
			{
				m_eButtonState = ButtonState_Hover;
				m_bShouldUpdateUITexture = true;
			}
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseLeaveWindowArea()
	{
		__super::OnMouseLeaveWindowArea();
		if (m_bEnable)
		{
			if (m_eButtonState != ButtonState_Normal)
			{
				m_eButtonState = ButtonState_Normal;
				m_bShouldUpdateUITexture = true;
			}
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseLeftButtonClickDown()
	{
		__super::OnMouseLeftButtonClickDown();
		if (m_bEnable)
		{
			if (m_eButtonState != ButtonState_PushDown)
			{
				m_eButtonState = ButtonState_PushDown;
				m_bShouldUpdateUITexture = true;
			}
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseLeftButtonClickUp()
	{
		__super::OnMouseLeftButtonClickUp();
		if (m_bEnable)
		{
			if (m_bMouseInWindowArea)
			{
				if (m_eButtonState != ButtonState_Hover)
				{
					m_eButtonState = ButtonState_Hover;
					m_bShouldUpdateUITexture = true;
				}
			}
			else
			{
				if (m_eButtonState != ButtonState_Normal)
				{
					m_eButtonState = ButtonState_Normal;
					m_bShouldUpdateUITexture = true;
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------
