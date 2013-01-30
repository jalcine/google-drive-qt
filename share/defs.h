#ifndef DEF_H
#define DEF_H

#define GET_FULL_ROOT_CONTENT QString("https://docs.google.com/feeds/default/private/full/folder%3Aroot/contents")
#define GET_FILES_IN_FOLDER QString("https://docs.google.com/feeds/default/private/full/")
#define ROOT_TAG QString("https://docs.google.com/feeds/default/private/full/folder%3Aroot")
#define PARENT_TAG QString("http://schemas.google.com/docs/2007#parent")
#define UPLOAD_TAG QString("http://schemas.google.com/g/2005#resumable-create-media")
#define ICON_TAG QString("http://schemas.google.com/docs/2007#icon")

#define CONTENTS QString("/contents")
#define MAX_RESULTS QString("?max-results=10000")

#define HIERARCHY_ATTRIBUTE_TAG(param) param("rel")
#define FYLE_TYPE_ATTRIBUTE_TAG(param) param("type")
#define FYLE_TYPE_SRC_ATTRIBUTE_TAG(param) param("src");
#define HIERARCHY_VALUE_TAG(param) param("href")
#define SELF_TAG QString("self")
#define FOLDER_TITLE_TAG QString("title")
#define FILE_TITLE_TAG QString("docs:filename")
#define FILE_SIZE_TAG QString("docs:size")
#define PUBLISHED_FILE_TAG QString("published")
#define UPDATED_FILE_TAG QString("updated")
#define EDITED_FILE_TAG QString("app:edited")
#define AUTHOR_TAG QString("author")
#define ENTRY_TAG QString("entry")

#define FOLDER_TYPE 0
#define FILE_TYPE 1

#define FOLDER_TYPE_STR QString("folder")
#define FILE_TYPE_STR QString("file")
#define CONTENT QString("content")
#define ACCOUNT_SEPARATOR_BEGIN QString("[ ")
#define ACCOUNT_SEPARATOR_END QString(" ]")

#define ACCOUNTS_GROUP QString("Accounts")
#define COMMON_GROUP QString("Common")
#define PANEL_GROUP QString("Panel")
#define ACCESS_TOKEN_KEY QString("access_token")
#define REFRESH_TOKEN_KEY QString("refresh_token")
#define WORK_DIR_KEY QString("workingDirectory")
#define INIT_LOAD_KEY QString("initialLoad")
#define CURRENT_PANEL_KEY QString("currentPanel")
#define CURRENT_FOLDER_URL_KEY QString("currentFolderUrl")
#define CURRENT_FOLDER_PATH_KEY QString("currentFolderPath")
#define PATHES_URLS_KEY QString("pathesUrls")
#define LEFT_PANEL_VALUE 0
#define RIGHT_PANEL_VALUE 1
#define CURRENT_ACCOUNT_KEY QString("currentAccount")
#define ACCOUNT_LETTER_KEY QString("letter")
#define NAME_KEY QString("name")
#define DOMAIN_SHARING_POLICY_KEY QString("domainSharingPolicy")
#define PERMISSION_ID_KEY QString("permissionId")
#define QUOTA_BYTES_TOTAL_KEY QString("quotaBytesTotal")
#define QUOTA_BYTES_USED_KEY QString("quotaBytesUsed")
#define QUOTA_BYTES_USED_IN_TRASH_KEY QString("quotaBytesUsedInTrash")
#define SCOPE_KEY QString("scope")
#define CLIENT_ID_KEY QString("clientId")
#define CLIENT_SECRET_KEY QString("clientSecret")
#define REDIRECT_URI_KEY QString("redirectUri")
#define ITEM_SORT_ORDER QString("itemSortOrder")
#define SORT_ORDER QString("sortOrder")
#define PANEL_HEADER_STATE QString("panelHeaderState")

#define PARENT_FOLDER_SIGN QString("[..]")

#endif // DEF_H
