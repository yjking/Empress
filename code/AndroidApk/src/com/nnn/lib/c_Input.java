package com.nnn.lib;

// ����
class c_TouchPoint
{
	public int	m_x;
	public int	m_y;
	public int	m_id;
};


// ������Ϣ����
class c_MessageType
{
	// m_wParam = <�����¼��Ĵ�������>��m_lParam = <��ǰ�Ĵ������������ Up �¼����򴥵����� +1>
	final static int Down			= 0;	// ���㰴���¼��������¼�ǰ�Ĵ����� = 1 ʱ�������� > 1���򴥷� MULTI_TOUCH_DOWN��
	final static int Up				= 1;	// �����ɿ��¼��������¼�ǰ�Ĵ����� = 1 ʱ�������� > 1���򴥷� MULTI_TOUCH_UP��
	final static int Move			= 2;	// �����ƶ��¼���ע�⣺�������¼��Ĵ���������Զ�� 0��
	final static int Cancel			= 3;	// ����ȡ���¼�
	//final static int Outside		= 4;
	final static int PointerDown	= 5;	// ���㰴���¼��������¼�ǰ�Ĵ����� > 1 ʱ�������� = 1���򴥷� TOUCH_DOWN��
	final static int PointerUp		= 6;	// �����ɿ��¼��������¼�ǰ�Ĵ����� > 1 ʱ�������� = 1���򴥷� TOUCH_UP��
};


// �豸����ת����
class c_RotationType
{
	final static int Unspecified	= 0;	// δָ��
	final static int Identity		= 1;	// ��ʼ��ת����
	final static int Rotate90		= 2;	// ��ʱ��ת 90 ��
	final static int Rotate180		= 3;	// ��ת 180 ��
	final static int Rotate270		= 4;	// ��ʱ��ת 270 ��
};
