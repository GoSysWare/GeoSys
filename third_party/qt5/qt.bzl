load("@rules_cc//cc:defs.bzl", "cc_library")

def _file_name(filePathName):
    if "/" in filePathName:
        return filePathName.rsplit("/", -1)[1]
    else:
        return filePathName

def _base_name(fileName):
    return fileName.split(".")[0]

def qt_cc_library(name, srcs, hdrs, copts = [], uis = [], res = [], normal_hdrs = [], deps = None, **kwargs):
    print(hdrs)
  
    for hItem in hdrs:
        base_name = _base_name(_file_name(hItem))
        cmd = """
        if grep -q Q_OBJECT $(location %s); then \
            /usr/local/Qt5.14.2/5.14.2/gcc_64/bin/moc $(location %s) -o $@ -f'%s'; \
        else \
            echo '' > $@ ; \
        fi""" % (hItem, hItem, "%s/%s" % (native.package_name(), hItem))
        native.genrule(
            name = "%s_moc" % base_name,
            srcs = [hItem],
            outs = ["moc_%s.cpp" % base_name],
            cmd = cmd,
        )
        print(cmd)
        srcs.append("moc_%s.cpp" % base_name)
    print(srcs)
    for uitem in uis:
        base_name = _base_name(_file_name(uitem))
        native.genrule(
            name = "%s_ui" % base_name,
            srcs = [uitem],
            outs = ["ui_%s.h" % base_name],
            cmd = "/usr/local/Qt5.14.2/5.14.2/gcc_64/bin/uic $(locations %s) -o $@" % uitem,
        )
        hdrs.append("ui_%s.h" % base_name)

    for ritem in res:
        base_name = _base_name(_file_name(ritem))
        native.genrule(
            name = "%s_res" % base_name,
            srcs = [ritem] + deps,
            outs = ["res_%s.cpp" % base_name],
            cmd = "/usr/local/Qt5.14.2/5.14.2/gcc_64/bin/rcc --name res --output $(OUTS) $(location %s)" % ritem,
        )
        srcs.append("res_%s.cpp" % base_name)

    hdrs = hdrs + normal_hdrs
    cc_library(
        name = name,
        srcs = srcs,
        hdrs = hdrs,
        deps = deps,
        copts = copts + ["-fPIC"],
        alwayslink = 1,
        **kwargs
    )
