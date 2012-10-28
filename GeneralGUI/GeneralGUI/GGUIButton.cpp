﻿//-----------------------------------------------------------------------------
// GGUI Button控件
// (C) oil
// 2012-09-30
//-----------------------------------------------------------------------------
#include "GGUIStdAfx.h"
#include "GGUIButton.h"
//-----------------------------------------------------------------------------
namespace GGUI
{
	GGUIButton::GGUIButton()
	:GGUIWindow()
	,m_eButtonState(ButtonState_Normal)
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
				m_bDirty = true;
			}
		}
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseEnterWindowArea()
	{
		if (m_bEnable)
		{
			if (m_eButtonState != ButtonState_Hover)
			{
				m_eButtonState = ButtonState_Hover;
				m_bDirty = true;
			}
		}
		__super::OnMouseEnterWindowArea();
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseLeaveWindowArea()
	{
		if (m_bEnable)
		{
			if (m_eButtonState != ButtonState_Normal)
			{
				m_eButtonState = ButtonState_Normal;
				m_bDirty = true;
			}
		}
		__super::OnMouseLeaveWindowArea();
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseLeftButtonClickDown()
	{
		if (m_bEnable)
		{
			if (m_eButtonState != ButtonState_PushDown)
			{
				m_eButtonState = ButtonState_PushDown;
				m_bDirty = true;
			}
		}
		__super::OnMouseLeftButtonClickDown();
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::OnMouseLeftButtonClickUp()
	{
		if (m_bEnable)
		{
			if (m_bMouseInWindowArea)
			{
				if (m_eButtonState != ButtonState_Hover)
				{
					m_eButtonState = ButtonState_Hover;
					m_bDirty = true;
				}
			}
			else
			{
				if (m_eButtonState != ButtonState_Normal)
				{
					m_eButtonState = ButtonState_Normal;
					m_bDirty = true;
				}
			}
		}
		__super::OnMouseLeftButtonClickUp();
	}
	//-----------------------------------------------------------------------------
	void GGUIButton::GenerateRenderUnit(stRenderUnit& theRenderUnit)
	{
		static SoFloat s_fColorReduce = 1.0f;
		static SoFloat s_fDeltaX = 2.0f;
		static SoFloat s_fDeltaY = 2.0f;

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
		theRenderUnit.fPositionX = fDestPosX;
		theRenderUnit.fPositionY = fDestPosY;
		theRenderUnit.fPositionZ = m_fPositionZ;
		theRenderUnit.fWidth = m_fWidth;
		theRenderUnit.fHeight = m_fHeight;
		theRenderUnit.fColorR = fDestColorR;
		theRenderUnit.fColorG = fDestColorG;
		theRenderUnit.fColorB = fDestColorB;
		theRenderUnit.fColorA = m_fColorA;
		theRenderUnit.theImagesetID = m_nMyImagesetID;
		theRenderUnit.theImageRectID = m_nMyImageRectID;
	}
}
//-----------------------------------------------------------------------------
