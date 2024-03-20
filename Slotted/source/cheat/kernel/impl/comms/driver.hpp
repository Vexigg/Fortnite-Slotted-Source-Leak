#ifndef DRIVER_HPP
#define DRIVER_HPP
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdio.h>
#include <string_view>
#include <iostream>
#include <chrono>

#define DEVICE "\\\\.\\{skardrv}"

struct IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PVOID Pointer;
	};
	ULONG_PTR Information;
};

using PIO_STATUS_BLOCK = IO_STATUS_BLOCK*;
using PIO_APC_ROUTINE = void(NTAPI*)(
	PVOID,
	PIO_STATUS_BLOCK,
	std::uint32_t);

extern "C" __int64 direct_device_control(
	HANDLE FileHandle,
	HANDLE Event,
	PIO_APC_ROUTINE ApcRoutine,
	PVOID ApcContext,
	PIO_STATUS_BLOCK IoStatusBlock,
	std::uint32_t IoControlCode,
	PVOID InputBuffer,
	std::uint32_t InputBufferLength,
	PVOID OutputBuffer,
	std::uint32_t OutputBufferLength);

namespace driver
{
	class comms
	{
		typedef enum _requests
		{
			invoke_start,
			invoke_base,
			invoke_region,
			invoke_read,
			invoke_write,
			invoke_pattern,
			invoke_success,
			invoke_unique,
			invoke_mouse,
			invoke_translate,
			invoke_read_kernel,
			invoke_dtb,

		}requests, * prequests;

		typedef struct _read_invoke {
			uint32_t pid;
			uintptr_t address;
			void* buffer;
			size_t size;
		} read_invoke, * pread_invoke;

		typedef struct _write_invoke {
			uint32_t pid;
			uintptr_t address;
			void* buffer;
			size_t size;
		} write_invoke, * pwrite_invoke;

		typedef struct _base_invoke {
			uint32_t pid;
			uintptr_t handle;
			const char* name;
			size_t size;
		} base_invoke, * pbase_invoke;

		typedef struct _region_invoke {
			uintptr_t address;
		} region_invoke, * pregion_invoke;

		typedef struct _invoke_data
		{
			uint32_t unique;
			requests code;
			void* data;
		}invoke_data, * pinvoke_data;

		typedef struct _read_kernel_invoke {
			uintptr_t address;
			void* buffer;
			size_t size;
			uint32_t memory_type;
		} read_kernel_invoke, * pread_kernel_invoke;

		typedef struct _translate_invoke {
			uintptr_t virtual_address;
			uintptr_t directory_base;
			void* physical_address;
		} translate_invoke, * ptranslate_invoke;

		typedef struct _dtb_invoke {
			uint32_t pid;
			uintptr_t dtb;
		} dtb_invoke, * pdtb_invoke;


		std::int32_t m_pid = 0;
		HANDLE m_handle = 0;

	public:

		std::uintptr_t image_base = 0;
		std::uintptr_t dtb = 0;

		[[nodiscard]] bool send_cmd(void* data, requests code);
		[[nodiscard]] bool initialize_handle();
		[[nodiscard]] bool attach(int a_pid);
		[[nodiscard]] bool get_cr3(std::uintptr_t base_address);
		//[[nodiscard]] const std::uint32_t get_process_pid( const std::wstring& proc_name );
		[[nodiscard]] const std::uintptr_t get_dtb(std::uint32_t pid);
		[[nodiscard]] const std::uintptr_t get_image_base(const char* module_name);
		[[nodiscard]] const std::uintptr_t translate_address(std::uintptr_t virtual_address, std::uintptr_t directory_base);

		[[nodiscard]] bool read_kernel(const uintptr_t address, void* buffer, const size_t size, const uint32_t memory_type);
		[[nodiscard]] bool read_virtual(const uintptr_t address, void* buffer, const size_t size);
		[[nodiscard]] bool write_virtual(const uintptr_t address, void* buffer, const size_t size);

		template <typename t>
		[[nodiscard]] auto write(const uintptr_t address, t value) -> bool
		{
			return this->write_virtual(address, &value, sizeof(t));
		}

		template <typename t>
		[[nodiscard]] auto read(const uintptr_t address) -> t
		{
			t response{};
			this->read_virtual(address, &response, sizeof(t));
			return response;
		}

		template <typename t>
		[[nodiscard]] auto read_array(const uintptr_t address, t buffer, size_t size) -> bool
		{
			return this->read_virtual(address, buffer, size);
		}
	};
}
// can create a global instance, or call it
static driver::comms* request = new driver::comms();


#endif // include guard
