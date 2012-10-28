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
}
//-----------------------------------------------------------------------------
