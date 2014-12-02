#pragma once
namespace Heck
{
	template<typename T,class _Arg1,class _Result>
	struct binary_function1
	{
		typedef		T	class_ptr_type;	
		typedef _Arg1	first_argument_type;
		typedef _Result result_type;
	};

	template<class _Result,class _Ty,class _Arg1>
	class mem_fun_1:public binary_function1<_Ty *, _Arg1,_Result>
	{
	public:
		mem_fun_1(_Result (_Ty::*_Pm)(_Arg1)): _Pmemfun(_Pm)
		{
		}

		_Result operator()(_Ty *_Pleft, _Arg1 arg1)
		{
			return ((_Pleft->*_Pmemfun)(arg1));
		}

	private:
		_Result (_Ty::*_Pmemfun)(_Arg1);
	};

	template<typename _Result,typename _Ty,typename _Arg1> 
	mem_fun_1<_Result, _Ty,_Arg1> mem_fun1(_Result (_Ty::*_Pm)(_Arg1))
	{
		return (mem_fun_1<_Result, _Ty,_Arg1>(_Pm));
	}
	template<class _Arg1,class _Result>
	struct unary_function1
	{
		typedef _Arg1	first_argument_type;
		typedef _Result result_type;
	};

	template<class _Fn1>
	class binder1: public unary_function1<typename _Fn1::first_argument_type,typename _Fn1::result_type>
	{
	public:
		typedef unary_function1<typename _Fn1::first_argument_type,typename _Fn1::result_type> _Base;
		typedef typename _Base::first_argument_type first_argument_type;
		typedef typename _Base::result_type result_type;

		binder1(_Fn1& _Func,typename _Fn1::class_ptr_type& obj_ptr):op(_Func),value(obj_ptr)
		{
		}

		result_type operator()(first_argument_type& arg1)
		{
			return (op(value, arg1));
		}

	protected:
		_Fn1		op;	
		typename _Fn1::class_ptr_type value;
	};

	template<class _Fn1,class _Ty>
	inline	binder1<_Fn1> bind1(_Fn1& _Func,_Ty& _Left)
	{
		typename _Fn1::class_ptr_type _Val(_Left);
		return (binder1<_Fn1>(_Func, _Val));
	}
}