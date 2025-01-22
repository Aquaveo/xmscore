"""
conanfile.py for the xmscore project.
"""
from xmsconan.xms_conan2_file import XmsConan2File


class XmscoreConanFile(XmsConan2File):
    """
    XmscoreConanFile class used for defining the conan info.
    """
    name = "xmscore"
    url = "https://github.com/Aquaveo/xmscore"
    description = "Support library for XMS products"
    xms_dependencies = [
    ]
    

LIBRARY_NAME = XmscoreConanFile.name
