#pragma once

/*! \class NonCopyable
*/
class __declspec(novtable) NonCopyable
{
public:
	NonCopyable()
	{
	}

	~NonCopyable()
	{
	}

public:
	NonCopyable(const NonCopyable &);
	const NonCopyable& operator=(const NonCopyable &);
};