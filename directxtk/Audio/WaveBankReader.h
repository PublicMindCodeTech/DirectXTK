//--------------------------------------------------------------------------------------
// File: WaveBankReader.h
//
// Functions for loading audio data from Wave Banks
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//-------------------------------------------------------------------------------------

#pragma once

#ifdef __cplusplus
EXTERN_C_BEGIN
#endif

NAMESPACE_DirectX

class DXTKAPI WaveBankReader
{
public:
	WaveBankReader();
	~WaveBankReader();

	HRESULT Open(_In_z_ const wchar_t* szFileName);

	uint32_t Find(_In_z_ const char* name) const;

	bool IsPrepared();
	void WaitOnPrepare();

	bool HasNames() const;
	bool IsStreamingBank() const;

#if defined(_XBOX_ONE) && defined(_TITLE)
	bool HasXMA() const;
#endif

	const char* BankName() const;

	uint32_t Count() const;

	uint32_t BankAudioSize() const;

	HRESULT GetFormat(_In_ uint32_t index, _Out_ WAVEFORMATEX* pFormat, _In_ size_t maxsize) const;

	HRESULT GetWaveData(_In_ uint32_t index, _Outptr_ const uint8_t** pData, _Out_ uint32_t& dataSize) const;

	HRESULT GetSeekTable(_In_ uint32_t index, _Out_ const uint32_t** pData, _Out_ uint32_t& dataCount, _Out_ uint32_t& tag) const;

	HANDLE GetAsyncHandle() const;

	struct Metadata
	{
		uint32_t    duration;
		uint32_t    loopStart;
		uint32_t    loopLength;
		uint32_t    offsetBytes;
		uint32_t    lengthBytes;
	};
	HRESULT GetMetadata(_In_ uint32_t index, _Out_ Metadata& metadata) const;

private:
	// Private implementation.
	class Impl;

	std::unique_ptr<Impl> pImpl;

	// Prevent copying.
	WaveBankReader(WaveBankReader const&);
	WaveBankReader& operator= (WaveBankReader const&);
};

NAMESPACE_DirectX_END

#ifdef __cplusplus
EXTERN_C_END
#endif