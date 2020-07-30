#pragma once

wchar_t* to_unicode(const char* utf8_string)
{
	int err;
	wchar_t* res;
	int res_len = MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, NULL, 0);
	if (res_len == 0) { return NULL; }
	res = (wchar_t *)calloc(sizeof(wchar_t), res_len);
	if (res == NULL) { return NULL; }
	err = MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, res, res_len);
	if (err == 0)
	{
		free(res);
		return NULL;
	}
	return res;
}

char* to_cp1251(wchar_t* unicode_string)
{
	int err;
	char* res;
	int res_len = WideCharToMultiByte(1251, 0, unicode_string, -1, NULL, 0, NULL, NULL);
	if (res_len == 0) { return NULL; }
	res = (char *)calloc(sizeof(char), res_len);
	if (res == NULL) { return NULL; }
	err = WideCharToMultiByte(1251, 0, unicode_string, -1, res, res_len, NULL, NULL);
	if (err == 0)
	{
		free(res);
		return NULL;
	}
	return res;
}

wchar_t* cp1251_to_unicode(const char* utf8_string)
{
	int err;
	wchar_t* res;
	int res_len = MultiByteToWideChar(
		1251,
		0,
		utf8_string,
		-1,
		NULL,
		0
	);
	if (res_len == 0)
	{
		return NULL;
	}
	res = (wchar_t *)calloc(sizeof(wchar_t), res_len);
	if (res == NULL)
	{
		return NULL;
	}
	err = MultiByteToWideChar(
		1251,
		0,
		utf8_string,
		-1,
		res,
		res_len
	);
	if (err == 0)
	{
		free(res);
		return NULL;
	}
	return res;
}

char* unicode_to_utf8(wchar_t* unicode_string)
{
	int err;
	char* res;
	int res_len = WideCharToMultiByte(
		CP_UTF8,
		0,
		unicode_string,
		-1,
		NULL,
		0,
		NULL,
		NULL
	);
	if (res_len == 0)
	{
		return NULL;
	}
	res = (char *)calloc(sizeof(char), res_len);
	if (res == NULL)
	{
		return NULL;
	}
	err = WideCharToMultiByte(
		CP_UTF8,
		0,
		unicode_string,
		-1,
		res,
		res_len,
		NULL,
		NULL
	);
	if (err == 0)
	{
		free(res);
		return NULL;
	}
	return res;
}

wchar_t* mfunicode(const char* utf8_string)
{
	int err;
	wchar_t* res;
	int res_len = MultiByteToWideChar(1251, 0, utf8_string, -1, NULL, 0);
	if (res_len == 0)return NULL;
	res = (wchar_t *)calloc(sizeof(wchar_t), res_len);
	if (res == NULL)return NULL;
	err = MultiByteToWideChar(1251, 0, utf8_string, -1, res, res_len);
	if (err == 0)
	{
		free(res);
		return NULL;
	}
	return res;
}

char* mf_utf8(wchar_t* unicode_string)
{
	int err;
	char* res;
	int res_len = WideCharToMultiByte(CP_UTF8, 0, unicode_string, -1, NULL, 0, NULL, NULL);
	if (res_len == 0)return NULL;
	res = (char *)calloc(sizeof(char), res_len);
	if (res == NULL)
	{
		return NULL;
	}
	err = WideCharToMultiByte(CP_UTF8, 0, unicode_string, -1, res, res_len, NULL, NULL);
	if (err == 0)
	{
		free(res);
		return NULL;
	}
	return res;
}

enum EWstrToUTF8Constants
{
	eUTWC_MASKBITS = 0x3F,
	eUTWC_MASKIDBITS = 0xE0,
	eUTWC_MASK2BYTES = 0xC0
};

typedef std::string Str;
typedef std::wstring WStr;

void utf8_to_wStr(const char* str, WStr& dstr)
{
	WStr tmp;

	const size_t length = strlen(str);
	tmp.resize(length);
	tmp.clear();

	const unsigned char* const src = (unsigned char*)str;

	for (size_t i = 0; i < length;)
	{
		if (src[i] < 0x80)
		{
			tmp.append(1, (wchar_t)src[i]);
			++i;
		}
		else if ((src[i] & eUTWC_MASKIDBITS) == eUTWC_MASK2BYTES)
		{
			wchar_t d = (wchar_t)(src[i] & ~eUTWC_MASKIDBITS) << 6;
			wchar_t e = (wchar_t)(src[i + 1] & eUTWC_MASKBITS);
			wchar_t f = d | e;
			tmp.append(1, f);
			i += 2;
		}
		else
		{
			wchar_t d = (wchar_t)(src[i] & ~eUTWC_MASKIDBITS) << 12;
			wchar_t e = (wchar_t)(src[i + 1] & eUTWC_MASKBITS) << 6;
			wchar_t f = (wchar_t)(src[i + 2] & eUTWC_MASKBITS);
			wchar_t g = d | e | f;
			tmp.append(1, g);
			i += 3;
		}
	}dstr.assign(tmp.data(), tmp.length());
}

wchar_t* ansi_to_unicode(const char* utf8_string)
{
	int err;
	wchar_t* res;
	int res_len = MultiByteToWideChar(CP_ACP, 0, utf8_string, -1, NULL, 0);
	if (res_len == 0) { return NULL; }
	res = (wchar_t *)calloc(sizeof(wchar_t), res_len);
	if (res == NULL) { return NULL; }
	err = MultiByteToWideChar(CP_ACP, 0, utf8_string, -1, res, res_len);
	if (err == 0)
	{
		free(res);
		return NULL;
	}
	return res;
}
