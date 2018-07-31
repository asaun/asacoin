package=miniupnpc
$(package)_version=1.9.20140701
$(package)_download_path=http://octk4wj3v.bkt.clouddn.com
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=9d0369208087b9d8e8fe701e187c9f3f518794af15e3d00964478ccd4042c32b

define $(package)_set_vars
$(package)_build_opts=CC="$($(package)_cc)"
$(package)_build_opts_darwin=OS=Darwin
$(package)_build_opts_mingw32=-f Makefile.mingw
$(package)_build_env+=CFLAGS="$($(package)_cflags) $($(package)_cppflags)" AR="$($(package)_ar)"
endef

define $(package)_preprocess_cmds
  mkdir dll && \
  sed -e 's|MINIUPNPC_VERSION_STRING \"version\"|MINIUPNPC_VERSION_STRING \"$($(package)_version)\"|' -e 's|OS/version|$(host)|' miniupnpcstrings.h.in > miniupnpcstrings.h && \
  sed -i.old "s|miniupnpcstrings.h: miniupnpcstrings.h.in wingenminiupnpcstrings|miniupnpcstrings.h: miniupnpcstrings.h.in|" Makefile.mingw
endef

define $(package)_build_cmds
	$(MAKE) libminiupnpc.a $($(package)_build_opts)
endef

define $(package)_stage_cmds
	mkdir -p $($(package)_staging_prefix_dir)/include/miniupnpc $($(package)_staging_prefix_dir)/lib &&\
	install *.h $($(package)_staging_prefix_dir)/include/miniupnpc &&\
	install libminiupnpc.a $($(package)_staging_prefix_dir)/lib
endef
