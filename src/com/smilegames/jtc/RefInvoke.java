package com.smilegames.jtc;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class RefInvoke {

	/** @see #findMethodExact(Class, String, Object...) */
	public static Method findMethodExact(String className,
			ClassLoader classLoader, String methodName,
			Class<?>... parameterTypes) {

		try {
			Class<?> clazz = classLoader.loadClass(className);
			Method method = clazz.getDeclaredMethod(methodName, parameterTypes);
			method.setAccessible(true);
			return method;
		} catch (NoSuchMethodException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

	public static Object getTypedFieldObject(ClassLoader classLoader,
			String class_name, Object entity, String field_type,
			String field_name) {
		try {
			Class<?> obj_class = classLoader.loadClass(class_name);
			Field[] allField = obj_class.getDeclaredFields();
			for (int i = 0; i < allField.length; i++) {
				// Logger.log_behavior("getTypedFieldObject:" +
				// allField[i].getName() + " " +
				// allField[i].getType().getName());
				// Logger.log_behavior("input param = " + field_name + " "+
				// field_type);
				if (allField[i].getType().getName().equals(field_type)
						&& allField[i].getName().equals(field_name)) {
					allField[i].setAccessible(true);
					return allField[i].get(entity);
				}
			}
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// Logger.log_behavior("-------------------not fond typed field!");
		return null;
	}

	public static void setTypedFieldOjbect(ClassLoader classLoader,
			String classname, String field_type, String filedName, Object obj,
			Object filedVaule) {
		try {

			Class<?> obj_class = classLoader.loadClass(classname);
			Field[] allField = obj_class.getDeclaredFields();
			for (int i = 0; i < allField.length; i++) {
				// Logger.log_behavior("getTypedFieldObject:" +
				// allField[i].getName() + " " +
				// allField[i].getType().getName());
				if (allField[i].getType().getName().equals(field_type)
						&& allField[i].getName().equals(filedName)) {
					allField[i].setAccessible(true);
					allField[i].set(obj, filedVaule);
					return;
				}
			}

		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static Object getTypedStaticFieldOjbect(ClassLoader classLoader,
			String class_name, String filedName) {

		try {
			Class<?> obj_class = classLoader.loadClass(class_name);
			Field field = obj_class.getDeclaredField(filedName);
			field.setAccessible(true);
			return field.get(null);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;

	}

	public static void setTypedStaticOjbect(ClassLoader classLoader,
			String class_name, String filedName, Object filedVaule) {
		try {
			Class<?> obj_class = classLoader.loadClass(class_name);
			Field field = obj_class.getDeclaredField(filedName);
			field.setAccessible(true);
			field.set(null, filedVaule);
			// Logger.log_behavior("参数设置成功：" + class_name + "." + filedName);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static Object invokeStaticMethod(ClassLoader classLoader,
			String class_name, String method_name, Class<?>[] pareTyple,
			Object[] pareVaules) {

		try {
			Class<?> obj_class = classLoader.loadClass(class_name);
			Method method = obj_class.getDeclaredMethod(method_name, pareTyple);
			method.setAccessible(true);
			return method.invoke(null, pareVaules);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;

	}

	public static Object invokeTypedMethod(ClassLoader classLoader,
			String class_name, String method_name, Object obj, String retType,
			Class<?>[] pareTyple, Object[] pareVaules) {

		try {
			Class<?> obj_class = classLoader.loadClass(class_name);

			Method[] allMethods = obj_class.getDeclaredMethods();
			for (int i = 0; i < allMethods.length; i++) {
				// 这里还需要比较参数，暂时先不完善
				if (allMethods[i].getReturnType().getName().equals(retType)
						&& allMethods[i].getName().equals(method_name)) {
					allMethods[i].setAccessible(true);
					return allMethods[i].invoke(obj, pareVaules);
				}
			}

		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;

	}

	public static Object invokeMethod(ClassLoader classLoader,
			String class_name, String method_name, Object obj,
			Class<?>[] pareTyple, Object[] pareVaules) {

		try {
			Class<?> obj_class = classLoader.loadClass(class_name);
			Method method = obj_class.getDeclaredMethod(method_name, pareTyple);
			method.setAccessible(true);
			return method.invoke(obj, pareVaules);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;

	}

	public static Object invokeDeclaredMethod(String class_name,
			String method_name, Object obj, Class<?>[] pareTyple,
			Object[] pareVaules) {

		try {
			Class<?> obj_class = Class.forName(class_name);
			Method method = obj_class.getDeclaredMethod(method_name, pareTyple);
			method.setAccessible(true);
			return method.invoke(obj, pareVaules);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;

	}

	public static int getFieldInt(String class_name, Object obj,
			String filedName) {
		try {
			Class<?> obj_class = Class.forName(class_name);
			Field field = obj_class.getDeclaredField(filedName);
			field.setAccessible(true);
			return field.getInt(obj);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return -1;

	}

	public static Object getFieldOjbect(ClassLoader classLoader,
			String class_name, Object obj, String filedName) {
		try {
			Class<?> obj_class = classLoader.loadClass(class_name);
			Field field = obj_class.getDeclaredField(filedName);
			field.setAccessible(true);
			return field.get(obj);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;

	}

	public static Object getStaticFieldOjbect(String class_name,
			String filedName) {

		try {
			Class<?> obj_class = Class.forName(class_name);
			Field field = obj_class.getDeclaredField(filedName);
			field.setAccessible(true);
			return field.get(null);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;

	}

	public static void setFieldOjbect(String classname, String filedName,
			Object obj, Object filedVaule) {
		try {
			Class<?> obj_class = Class.forName(classname);
			Field field = obj_class.getDeclaredField(filedName);
			field.setAccessible(true);
			field.set(obj, filedVaule);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static void setFieldInt(String className, String fieldName,
			Object obj, int value) {
		try {
			Class<?> obj_class = Class.forName(className);
			Field field = obj_class.getDeclaredField(fieldName);
			field.setAccessible(true);
			field.setInt(obj, value);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static void setStaticOjbect(String class_name, String filedName,
			Object filedVaule) {
		try {
			Class<?> obj_class = Class.forName(class_name);
			Field field = obj_class.getDeclaredField(filedName);
			field.setAccessible(true);
			field.set(null, filedVaule);
			// Logger.log_behavior("参数设置成功：" + class_name + "." + filedName);
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
